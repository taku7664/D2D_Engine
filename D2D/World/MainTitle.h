#pragma once
#include "../DemoApp.h"


class MainTitle
	: public World
{
public:
	virtual void WorldLoad();
	virtual void WorldDestroy();
	virtual void WorldEnter();
	virtual void WorldExit();
};

