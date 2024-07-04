#include "pch.h"
#include "RectRenderer.h"
#include "../../World/Object/Actor/Actor.h"
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

bool RectRenderer::Draw(Camera2D* _camera)
{
	Transform2D* tr = gameObject->transform;
	if (!tr) assert("transform is Nullptr");

	Vector2 center = { size.width / 2 + offset.x , size.height / 2 + offset.y }; 

	// 중앙을 축으로 회전 및 뒤집기 변환 행렬 설정
	D2D1_MATRIX_3X2_F transform =
		Transform2D::TranslateMatrix(-center.x, -center.y) * // 이미지의 중심축에 오프셋을 계산해서 이동
		tr->GetWorldMatrix() * // 월드 변환 적용
		Transform2D::TranslateMatrix(center.x, center.y) * // 다시 원래 위치로 이동
		_camera->CameraMatrix(); // 최종적으로 카메라 변환 적용

	ID2D1BitmapRenderTarget* renderTarget = _camera->GetBitmapRenderTarget();
	ID2D1SolidColorBrush* brush = D2DRender::GetBrush();
	D2D1_COLOR_F oldColor = brush->GetColor(); // 기존 색상 저장

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
	}

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	brush->SetColor(oldColor); // 기존 색상 돌려놓기

	return true;
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