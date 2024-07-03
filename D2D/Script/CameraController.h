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
				gameObject->transform->rotation += 1;
			}
			else
			{
				gameObject->transform->scale.x += 0.03f;
				gameObject->transform->scale.y += 0.03f;
			}
		}
		if (Input::KeyHold(34))
		{
			if (Input::KeyHold(17))
			{
				gameObject->transform->rotation -= 1;
			}
			else
			{
				gameObject->transform->scale.x -= 0.03f;
				gameObject->transform->scale.y -= 0.03f;
			}

		}
	}

};