#pragma once
#include "../DemoApp.h"


class TestScript : public Script
{
private:

public:

	void Update()
	{
		if (Input::KeyHold(SPACEBAR))
		{
			gameObject->transform->rotation += 90 * Time::deltaTime;
		}
		if (Input::KeyHold(LEFT))
		{
			gameObject->transform->scale.x = 1.f;
			gameObject->transform->position.x -= 5;
		}
		if (Input::KeyHold(RIGHT))
		{
			gameObject->transform->scale.x = -1.f;
			gameObject->transform->position.x += 5;
		}
		if (Input::KeyHold(UP))
		{
			gameObject->transform->position.y -= 4;
		}
		if (Input::KeyHold(DOWN))
		{
			gameObject->transform->position.y += 4;
		}
		gameObject->depthsLevel = gameObject->transform->position.y;
	}

	void OnCollisionEnter(Actor* collision)
	{
		Debug.Log("OnCollisionEnter()");
	}
	void OnCollisionStay(Actor* collision)
	{
		Debug.Log("OnCollisionStay()");
	}
	void OnCollisionExit(Actor* collision)
	{
		Debug.Log("OnCollisionExit()");
	}
};