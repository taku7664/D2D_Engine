#pragma once
#include "../DemoApp.h"


class TestScript : public Script
{
private:

public:

	float RotationSpeed = 1.f;

	void Update()
	{
		gameobject->transform->rotation += Time::deltaTime;
	}
};