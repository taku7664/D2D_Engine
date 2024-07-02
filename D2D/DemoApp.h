#pragma once
#include "../Engine/GameApp.h"
#include "Contents.h"

class DemoApp
	: public GameApp
{
public:

	DemoApp() {}
	~DemoApp() {}

	virtual void Initialize(HINSTANCE _hinstance, int _width, int _height, const wchar_t* _title) final;
	void LoadWorld();

};