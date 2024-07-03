#pragma once
#include "../Component.h"
#include "../Camera2D.h"
#include "../../World/Object/Object.h"
#include "../Script.h"

class Collider 
	: public Component
{
public:

	Collider();
	~Collider();

	virtual void Draw(Camera2D* _camera);

	void OnCollisionEnter(Object* other);
	void OnCollisionStay(Object* other);
	void OnCollisionExit(Object* other);

	bool isTrigger;

	Vector2 offset;

private:

};

// �پ��� �浹ó��
//https://yoojaejun.github.io/winapidirectx/WinAPI-2D-%EC%B6%A9%EB%8F%8C%EC%B2%B4%ED%81%AC-%EA%B3%B5%EB%B6%80/
// �������� �浹 �� �ݻ�
// https://paynter1127.blogspot.com/2019/08/blog-post_28.html
// ��ü���� �������� ����
//https://tt91.tistory.com/57