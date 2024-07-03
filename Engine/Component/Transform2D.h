#pragma once
#include "Component.h"

class Transform2D
	: public Component
{
public:

	Transform2D();
	virtual ~Transform2D();

	Vector2			 position = { 1,1 };
	float					 rotation = 0.f;
	Vector2			 scale = { 1,1 };

	virtual void			 Update() final;
	virtual void			 LateUpdate() final;
	void                     Release();

	Vector2			 WorldPosition();
	float					 WorldRotation();
	Vector2			 WorldScale();
	D2D1_MATRIX_3X2_F		 GetLocalMatrix() { return m_localMatrix; }
	D2D1_MATRIX_3X2_F		 GetWorldMatrix() { return m_worldMatrix; }
	void					 SetParent(Transform2D* _parent);
	Transform2D*			 GetParent() { return m_parent; }
	void					 LookAt(Transform2D* _target);

	static D2D1_MATRIX_3X2_F TranslateMatrix(float _x, float _y);
	static D2D1_MATRIX_3X2_F TranslateMatrix(Vector2 _xy);
	static D2D1_MATRIX_3X2_F RotationMatrix(float _rotation);
	static D2D1_MATRIX_3X2_F ScaleMatrix(float _xScale, float _yScale);

private:

	Transform2D*				    m_parent;         // �θ�
	std::vector<Transform2D*>       m_childList;      // �ڽĸ���Ʈ
	D2D_MATRIX_3X2_F				m_localMatrix;    // ��� ���� ��ȯ
	D2D_MATRIX_3X2_F				m_worldMatrix;    // �θ���� �ݿ��� ���� ��ȯ

	D2D_MATRIX_3X2_F CalculationWorldTransform();
};

