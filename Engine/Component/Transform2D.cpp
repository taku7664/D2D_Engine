#include "pch.h"
#include "Transform2D.h"
#include "../World/Object/Object.h"

Transform2D::Transform2D()
	: position({ 0.f,0.f }),
	rotation(0.f),
	scale({ 1.f , 1.f }),
	m_localMatrix(),
	m_worldMatrix()
{
	m_type = ComponentType::Transform2D;
}

Transform2D::~Transform2D()
{
}

void Transform2D::LateUpdate()
{
	m_localMatrix =
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y)) *
		D2D1::Matrix3x2F::Rotation(rotation) *
		D2D1::Matrix3x2F::Translation(position.x, position.y);

	Object* parent = GetOwner()->GetParent();

	if (parent != nullptr)
	{
		m_worldMatrix = m_localMatrix * parent->transform->m_worldMatrix;
	}
	else
	{
		m_worldMatrix = m_localMatrix;
	}
}

D2D_VECTOR_2F Transform2D::WorldPosition()
{
	// �θ� ������Ʈ�� ���� ��
	return { m_worldMatrix.dx, m_worldMatrix.dy };
}

float Transform2D::WorldRotation()
{
	if (this->GetOwner()->GetParent() != nullptr)
	{
		return this->GetOwner()->GetParent()->transform->WorldRotation() * this->rotation;
	}
	else
	{
		return this->rotation;
	}
}

D2D_VECTOR_2F Transform2D::WorldScale()
{
	if (this->GetOwner()->GetParent() != nullptr)
	{
		D2D_VECTOR_2F parentScale = this->GetOwner()->GetParent()->transform->WorldScale();
		return { parentScale.x * this->scale.x, parentScale.y * this->scale.y };
	}
	else
	{
		return this->scale;
	}
}

D2D1_MATRIX_3X2_F Transform2D::GetCenterMatrix(int _wid, int _hei)
{
	D2D1::Matrix3x2F center = D2D1::Matrix3x2F::Translation(_wid / 2, _hei / 2);
	D2D1InvertMatrix(&center);
	return center;
}

D2D1_MATRIX_3X2_F Transform2D::GetCenterMatrix(float _wid, float _hei)
{
	D2D1::Matrix3x2F center = D2D1::Matrix3x2F::Translation(_wid / 2, _hei / 2);
	D2D1InvertMatrix(&center);
	return center;
}

D2D1_MATRIX_3X2_F Transform2D::GetCenterMatrix(D2D_VECTOR_2F _size)
{
	D2D1::Matrix3x2F center = D2D1::Matrix3x2F::Translation(_size.x / 2, _size.y / 2);
	D2D1InvertMatrix(&center);
	return center;
}

D2D1_MATRIX_3X2_F Transform2D::GetOffSetMatrix(D2D_VECTOR_2F _offset)
{
	D2D1::Matrix3x2F offset = D2D1::Matrix3x2F::Translation(_offset.x / 2, _offset.y / 2);
	//D2D1InvertMatrix(&offset);
	return offset;
}

D2D1_MATRIX_3X2_F Transform2D::TranslateMatrix(float _wid, float _hei)
{
	D2D1::Matrix3x2F center = D2D1::Matrix3x2F::Translation(_wid, _hei);
	return center;
}

void Transform2D::LookAt(Transform2D* _target)
{
	float angle = atan2(
		_target->m_worldMatrix.dx - this->m_worldMatrix.dx,
		_target->m_worldMatrix.dy - this->m_worldMatrix.dy);
	this->rotation = -MathF.Radian2Degree(angle);
}