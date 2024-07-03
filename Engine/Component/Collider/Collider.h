#pragma once
#include "../Component.h"
#include "../Camera2D.h"
#include "../../World/Object/Object.h"

class Collider 
	: public Component
{
public:

	Collider();
	~Collider();

	virtual void Draw(Camera2D* _camera);

	void OnCollisionEnter(Actor* other);
	void OnCollisionStay(Actor* other);
	void OnCollisionExit(Actor* other);

	static void CollisionIDClear() { CollisionID = 1; }

	UINT32 GetID() { return m_id; }

	bool isTrigger;

	Vector2 offset;

protected:

	static UINT CollisionID;
	UINT32 m_id;
	D2D1_COLOR_F m_color = D2D1::ColorF(D2D1::ColorF::GreenYellow);

};

// �پ��� �浹ó��
//https://yoojaejun.github.io/winapidirectx/WinAPI-2D-%EC%B6%A9%EB%8F%8C%EC%B2%B4%ED%81%AC-%EA%B3%B5%EB%B6%80/
// �������� �浹 �� �ݻ�
// https://paynter1127.blogspot.com/2019/08/blog-post_28.html
// ��ü���� �������� ����
//https://tt91.tistory.com/57