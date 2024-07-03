#include "pch.h"
#include "RectRenderer.h"
#include "../../World/Object/Object.h"
#include "../../Render/D2DRender.h"
#include "../Camera2D.h"
#include "../Transform2D.h"

RectRenderer::RectRenderer()
	: isFill(true),
	isLine(true),
	lineWidth(1.f),
	m_fillcolor(D2D1::ColorF(D2D1::ColorF::White)),
	m_linecolor(D2D1::ColorF(D2D1::ColorF::Black))
{
	m_type = ComponentType::RectRenderer;
}

RectRenderer::~RectRenderer()
{
}

void RectRenderer::Draw(Camera2D* _camera)
{
	ID2D1BitmapRenderTarget* renderTarget = _camera->GetBitmapRenderTarget();
	ID2D1SolidColorBrush* brush = D2DRender::GetBrush();
	D2D1_COLOR_F oldColor = brush->GetColor(); // 기존 색상 저장

	Transform2D* tr = gameObject->transform;
	if (!tr) assert("transform is Nullptr");

	Vector2 center = { size.width / 2 + offset.x , size.height / 2 + offset.y }; 

	// 중앙을 축으로 회전 및 뒤집기 변환 행렬 설정
	D2D1_MATRIX_3X2_F transform =
		Transform2D::TranslateMatrix(-center.x, -center.y) * // 이미지의 중심축에 오프셋을 계산해서 이동
		tr->GetWorldMatrix() * // 월드 변환 적용
		Transform2D::TranslateMatrix(center.x, center.y) * // 다시 원래 위치로 이동
		_camera->CameraMatrix(); // 최종적으로 카메라 변환 적용

	renderTarget->SetTransform(transform);

	D2D1_RECT_F rect = D2D1::RectF(0, 0, size.width, size.height);

	if (isFill)
	{
		brush->SetColor(m_fillcolor);
		renderTarget->FillRectangle(rect, brush);
	}

	if (isLine)
	{
		brush->SetColor(m_linecolor);
		renderTarget->DrawRectangle(rect, brush);
		// 외곽선이 scale값에 따라 증가해버려서 직접 scale의 x, y값만큼 나눠줌
		//renderTarget->DrawLine(D2D1::Point2F(rect.left, rect.top), D2D1::Point2F(rect.right, rect.top), brush, lineWidth / tr->WorldScale().y); // 상
		//renderTarget->DrawLine(D2D1::Point2F(rect.left, rect.bottom), D2D1::Point2F(rect.right, rect.bottom), brush, lineWidth / tr->WorldScale().y); // 하
		//renderTarget->DrawLine(D2D1::Point2F(rect.left, rect.top), D2D1::Point2F(rect.left, rect.bottom), brush, lineWidth / tr->WorldScale().x); // 좌
		//renderTarget->DrawLine(D2D1::Point2F(rect.right, rect.top), D2D1::Point2F(rect.right, rect.bottom), brush, lineWidth / tr->WorldScale().x); // 우
	}

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	brush->SetColor(oldColor); // 기존 색상 돌려놓기
}

void RectRenderer::SetLineColor(D2D1_COLOR_F _color)
{
	m_linecolor = _color;
}

void RectRenderer::SetFillColor(D2D1_COLOR_F _color)
{
	m_fillcolor = _color;
}

void RectRenderer::SetLine(bool _val)
{
	isLine = _val;
}

void RectRenderer::SetFill(bool _val)
{
	isFill = _val;
}