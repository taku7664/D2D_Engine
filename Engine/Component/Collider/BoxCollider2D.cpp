#include "pch.h"
#include "BoxCollider2D.h"
#include "../../Render/D2DRender.h"	
#include "../../World/Object/Actor/Actor.h"

BoxCollider2D::BoxCollider2D()
	: size({ 0.f,0.f })
{
	m_type = ComponentType::BoxCollider2D;
}

BoxCollider2D::~BoxCollider2D()
{

}

void BoxCollider2D::Draw(Camera2D* _camera)
{
	if (true)
	{
		ID2D1BitmapRenderTarget* renderTarget = _camera->GetBitmapRenderTarget();
		ID2D1SolidColorBrush* brush = D2DRender::GetBrush();
		D2D1_COLOR_F oldColor = brush->GetColor(); // 기존 색상 저장

		Transform2D* tr = gameObject->transform;
		if (!tr) assert("transform is Nullptr");

		// 중앙을 축으로 회전 및 뒤집기 변환 행렬 설정
		D2D1_MATRIX_3X2_F transform =
			Transform2D::TranslateMatrix(offset.x, offset.y) *
			Transform2D::TranslateMatrix(tr->WorldPosition()) * // 월드 변환 적용
			//tr->GetWorldMatrix() * // 월드 변환 적용
			//Transform2D::TranslateMatrix(offset.x, offset.y) *
			_camera->CameraMatrix(); // 최종적으로 카메라 변환 적용

		renderTarget->SetTransform(transform);

		D2D1_RECT_F rect = D2D1::RectF(0, 0, size.width, size.height);

		// 외곽선 출력
		brush->SetColor(m_color);
		renderTarget->DrawRectangle(rect, brush);
		// 중심점 출력
		Vector2 center = { size.width / 2 , size.height / 2 };
		D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(center.x, center.y), 3.f, 3.f);
		renderTarget->DrawEllipse(ellipse, brush, 3.f);

		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		brush->SetColor(oldColor); // 기존 색상 돌려놓기
	}
}
