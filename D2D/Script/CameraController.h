#pragma once
#include "../DemoApp.h"

class CameraController : public Script
{
public:

	void Update()
	{
		if (Input::KeyHold(33))
		{
			if (Input::KeyHold(17))
			{
				gameobject->transform->rotation += 1;
			}
			else
			{
				gameobject->transform->scale.x += 0.03f;
				gameobject->transform->scale.y += 0.03f;
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
				gameobject->transform->scale.x -= 0.03f;
				gameobject->transform->scale.y -= 0.03f;
			}

		}
	}

};