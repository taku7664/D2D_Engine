#pragma once
#include "../DemoApp.h"

class CameraController : public Script
{
public:

	void Update()
	{

		if (Input::KeyHold(LEFT))
		{
			gameobject->transform->position.x += 3;
		}
		if (Input::KeyHold(RIGHT))
		{
			gameobject->transform->position.x -= 3;
		}
		if (Input::KeyHold(UP))
		{
			gameobject->transform->position.y += 3;
		}
		if (Input::KeyHold(DOWN))
		{
			gameobject->transform->position.y -= 3;
		}

		if (Input::KeyHold(33))
		{
			if (Input::KeyHold(17))
			{
				gameobject->transform->rotation += 1;
			}
			else
			{
				gameobject->transform->scale.x += 0.03;
				gameobject->transform->scale.y += 0.03;
			}
		}
		if (Input::KeyHold(34))
		{
			if (Input::KeyHold(17))
			{
				gameobject->transform->rotation -= 1;
			}
			else
			{
				gameobject->transform->scale.x -= 0.03;
				gameobject->transform->scale.y -= 0.03;
			}

		}
	}

};