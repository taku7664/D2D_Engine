#include "pch.h"
#include "Transform2D.h"
#include "../World/Object/Object.h"

Transform2D::Transform2D()
	: m_parent(nullptr),
	position({ 0.f,0.f }),
	rotation(0.f),
	scale({ 1.f , 1.f }),
	m_localMatrix(),
	m_worldMatrix()
{
	m_type = ComponentType::Transform2D;
}

Transform2D::~Transform2D()
{
	Release();
}

void Transform2D::Update()
{
	m_localMatrix =
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y)) *
		D2D1::Matrix3x2F::Rotation(rotation) *
		D2D1::Matrix3x2F::Translation(position.x, position.y);
}

void Transform2D::LateUpdate()
{
	if (m_parent != nullptr)
	{
		m_worldMatrix = m_localMatrix * m_parent->CalculationWorldTransform();
	}
	else
	{
		m_worldMatrix = m_localMatrix;
	}
}

void Transform2D::Release()
{
	// 부모가 이미 있는경우 부모의 자식리스트에서 제거하고 바꿔줘야함.
	if (m_parent)
	{
		for (auto child = m_parent->m_childList.begin();; ++child)
		{
			if ((*child) == this)
			{
				m_parent->m_childList.erase(child);
				return;
			}
		}
	}
}


D2D_MATRIX_3X2_F Transform2D::CalculationWorldTransform()
{
	if (m_parent)
	{
		return m_localMatrix * m_parent->CalculationWorldTransform();
	}
	else
	{
		return m_localMatrix;
	}
}

D2D_VECTOR_2F Transform2D::WorldPosition()
{
	return { m_worldMatrix.dx, m_worldMatrix.dy };
}

float Transform2D::WorldRotation()
{
	if (m_parent != nullptr)
	{
		return this->m_parent->WorldRotation() * this->rotation;
	}
	else
	{
		return this->rotation;
	}
}

D2D_VECTOR_2F Transform2D::WorldScale()
{
	if (m_parent != nullptr)
	{
		D2D_VECTOR_2F parentScale = this->m_parent->WorldScale();
		return { parentScale.x * this->scale.x, parentScale.y * this->scale.y };
	}
	else
	{
		return this->scale;
	}
}

D2D1_MATRIX_3X2_F Transform2D::TranslateMatrix(float _wid, float _hei)
{
	return D2D1::Matrix3x2F::Translation(_wid, _hei);
}

D2D1_MATRIX_3X2_F Transform2D::RotationMatrix(float _rotation)
{
	return  D2D1::Matrix3x2F::Rotation(_rotation);
}

D2D1_MATRIX_3X2_F Transform2D::ScaleMatrix(float _xScale, float _yScale)
{
	return D2D1::Matrix3x2F::Scale(D2D1::SizeF(_xScale, _yScale));
}

void Transform2D::SetParent(Transform2D* _parent)
{
	Release();
	m_parent = _parent;
	if (_parent != nullptr)
	{
		_parent->m_childList.push_back(this);
	}
}

void Transform2D::LookAt(Transform2D* _target)
{
	float angle = atan2(
		_target->m_worldMatrix.dx - this->m_worldMatrix.dx,
		_target->m_worldMatrix.dy - this->m_worldMatrix.dy);
	this->rotation = -MathF.Radian2Degree(angle);
}

