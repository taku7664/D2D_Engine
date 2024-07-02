#pragma once
#include "../DemoApp.h"


class TestScript : public Script
{
private:

public:

	void Update()
	{
		if (Input::KeyHold(KeyType::SPACEBAR))
		{
			gameobject->transform->rotation += 90 * Time::deltaTime;
		}
	}
};