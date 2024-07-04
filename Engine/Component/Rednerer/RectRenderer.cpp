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

	// �߾��� ������ ȸ�� �� ������ ��ȯ ��� ����
	D2D1_MATRIX_3X2_F transform =
		Transform2D::TranslateMatrix(-center.x, -center.y) * // �̹����� �߽��࿡ �������� ����ؼ� �̵�
		tr->GetWorldMatrix() * // ���� ��ȯ ����
		Transform2D::TranslateMatrix(center.x, center.y) * // �ٽ� ���� ��ġ�� �̵�
		_camera->CameraMatrix(); // ���������� ī�޶� ��ȯ ����

	ID2D1BitmapRenderTarget* renderTarget = _camera->GetBitmapRenderTarget();
	ID2D1SolidColorBrush* brush = D2DRender::GetBrush();
	D2D1_COLOR_F oldColor = brush->GetColor(); // ���� ���� ����

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

	brush->SetColor(oldColor); // ���� ���� ��������

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