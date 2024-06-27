#include "pch.h"
#include "SpriteRenderer2D.h"
#include "../../World/Object/Object.h"
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

	Transform2D* tr = GetOwner()->GetComponent<Transform2D>();
	if (!tr) assert("Transform is Nullptr");

	D2D1_SIZE_F size = bitmap->GetSize();
	D2D1_RECT_F rect = D2D1::RectF(0, 0, size.width, size.height);

	//renderTarget->SetTransform(Transform::GetCenterMatrix(size.width, size.height) * tr->GetWorldMatrix());
	renderTarget->SetTransform(
		Transform2D::TranslateMatrix(-size.width * 0.5, -size.height * 0.5) *
		tr->GetWorldMatrix() *
		_camera->CameraMatrix());

	renderTarget->DrawBitmap(bitmap);

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}
