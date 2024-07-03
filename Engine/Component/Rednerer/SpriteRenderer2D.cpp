#include "pch.h"
#include "SpriteRenderer2D.h"
#include "../../World/Object/Actor/Actor.h"
#include "../Camera2D.h"
#include "../Transform2D.h"

SpriteRenderer2D::SpriteRenderer2D()
{
	m_type = ComponentType::SpriteRenderer2D;
}

SpriteRenderer2D::~SpriteRenderer2D()
{
}

void SpriteRenderer2D::Draw(Camera2D* _camera)
{
	ID2D1BitmapRenderTarget* renderTarget = _camera->GetBitmapRenderTarget();

	Transform2D* tr = gameObject->transform;
	if (!tr) assert("Transform is Nullptr");

	size = bitmap->GetSize();
	Vector2 center = { size.width / 2 + offset.x , size.height / 2 + offset.y }; // offset이 과연 중심축과 같이 움직이는게 맞을까?

	// 중앙을 축으로 회전 및 뒤집기 변환 행렬 설정
	D2D1_MATRIX_3X2_F Transform =
		Transform2D::TranslateMatrix(-center.x, -center.y) * // 이미지의 중심축에 오프셋을 계산해서 이동
		tr->GetWorldMatrix() * // 월드 변환 적용
		Transform2D::TranslateMatrix(center.x, center.y) * // 다시 원래 위치로 이동
		_camera->CameraMatrix(); // 최종적으로 카메라 변환 적용

	renderTarget->SetTransform(Transform);

	renderTarget->DrawBitmap(bitmap, { 0, 0, size.width, size.height }, alpha);

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}
