#pragma once
#include "Component.h"

class Transform2D
	: public Component
{
public:

	Transform2D();
	virtual ~Transform2D();

	D2D_VECTOR_2F			 position = { 1,1 };
	float					 rotation = 0.f;
	D2D_VECTOR_2F			 scale = { 1,1 };

	virtual void			 Update() final;
	virtual void			 LateUpdate() final;
	void                     Release();

	D2D_VECTOR_2F			 WorldPosition();
	float					 WorldRotation();
	D2D_VECTOR_2F			 WorldScale();
	D2D1_MATRIX_3X2_F		 GetLocalMatrix() { return m_localMatrix; }
	D2D1_MATRIX_3X2_F		 GetWorldMatrix() { return m_worldMatrix; }
	void					 SetParent(Transform2D* _parent);
	Transform2D*			 GetParent() { return m_parent; }
	void					 LookAt(Transform2D* _target);

	static D2D1_MATRIX_3X2_F TranslateMatrix(float _wid, float _hei);
	static D2D1_MATRIX_3X2_F RotationMatrix(float _rotation);
	static D2D1_MATRIX_3X2_F ScaleMatrix(float _xScale, float _yScale);

private:

	Transform2D*				    m_parent;         // 부모
	std::vector<Transform2D*>       m_childList;      // 자식리스트
	D2D_MATRIX_3X2_F				m_localMatrix;    // 상대 복합 변환
	D2D_MATRIX_3X2_F				m_worldMatrix;    // 부모까지 반영된 최종 변환

	D2D_MATRIX_3X2_F CalculationWorldTransform();
};

