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
	Vector2 center = { size.width / 2 + offset.x , size.height / 2 + offset.y }; // offset�� ���� �߽���� ���� �����̴°� ������?

	// �߾��� ������ ȸ�� �� ������ ��ȯ ��� ����
	D2D1_MATRIX_3X2_F Transform =
		Transform2D::TranslateMatrix(-center.x, -center.y) * // �̹����� �߽��࿡ �������� ����ؼ� �̵�
		tr->GetWorldMatrix() * // ���� ��ȯ ����
		Transform2D::TranslateMatrix(center.x, center.y) * // �ٽ� ���� ��ġ�� �̵�
		_camera->CameraMatrix(); // ���������� ī�޶� ��ȯ ����

	renderTarget->SetTransform(Transform);

	renderTarget->DrawBitmap(bitmap, { 0, 0, size.width, size.height }, alpha);

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}
