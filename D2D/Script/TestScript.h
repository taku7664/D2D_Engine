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
			gameobject->transform->rotation += 90 * Time::deltaTime;
		}
		if (Input::KeyHold(LEFT))
		{
			gameobject->transform->scale.x = 1.f;
			gameobject->transform->position.x -= 5;
		}
		if (Input::KeyHold(RIGHT))
		{
			gameobject->transform->scale.x = -1.f;
			gameobject->transform->position.x += 5;
		}
		if (Input::KeyHold(UP))
		{
			gameobject->transform->position.y -= 4;
		}
		if (Input::KeyHold(DOWN))
		{
			gameobject->transform->position.y += 4;
		}
		gameobject->depthsLevel = gameobject->transform->position.y;
	}
};