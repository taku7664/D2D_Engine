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

// 다양한 충돌처리
//https://yoojaejun.github.io/winapidirectx/WinAPI-2D-%EC%B6%A9%EB%8F%8C%EC%B2%B4%ED%81%AC-%EA%B3%B5%EB%B6%80/
// 원끼리의 충돌 및 반사
// https://paynter1127.blogspot.com/2019/08/blog-post_28.html
// 전체적인 물리엔진 관련
//https://tt91.tistory.com/57