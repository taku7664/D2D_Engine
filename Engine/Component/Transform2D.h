#pragma once
#include "Component.h"

class Transform2D
	: public Component
{
public:

	Transform2D();
	~Transform2D();

	D2D_VECTOR_2F position = { 1,1 };
	float		  rotation = 0.f;
	D2D_VECTOR_2F scale = { 1,1 };

	virtual void LateUpdate() final;

	D2D_VECTOR_2F WorldPosition();
	float		  WorldRotation();
	D2D_VECTOR_2F WorldScale();

	D2D1_MATRIX_3X2_F GetLocalMatrix() { return m_localMatrix; }
	D2D1_MATRIX_3X2_F GetWorldMatrix() { return m_worldMatrix; }

	static D2D1_MATRIX_3X2_F GetCenterMatrix(int _wid, int _hei);
	static D2D1_MATRIX_3X2_F GetCenterMatrix(float _wid, float _hei);
	static D2D1_MATRIX_3X2_F GetCenterMatrix(D2D_VECTOR_2F _size);
	static D2D1_MATRIX_3X2_F GetOffSetMatrix(D2D_VECTOR_2F _offset);

	static D2D1_MATRIX_3X2_F TranslateMatrix(float _wid, float _hei);

	void LookAt(Transform2D* _target);

private:

	D2D_MATRIX_3X2_F	m_localMatrix;    // 상대 복합 변환
	D2D_MATRIX_3X2_F	m_worldMatrix;    // 부모까지 반영된 최종 변환
};

