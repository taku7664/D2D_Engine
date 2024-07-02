#pragma once
#include "pch.h"
#include "Render/D2DRender.h"
#include "World/Manager/WorldManager.h"
#include "Resource/Manager/ResourceManager.h"
#include "Physics/Manager/CollisionManager.h"

class GameApp
{
public:

	void Initialize(HINSTANCE _hinstance, int _width, int _height, const wchar_t* _title);

	void Run();

	void Release();

protected:

	void FixedUpdate();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
	void StateUpdate();

private:

	HWND InitializeWindow(HINSTANCE _hinstance, int _width, int _height, const wchar_t* _title);

	static void CenterOfScreen(HWND _hwnd);
	static LRESULT CALLBACK WndProc(HWND _hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

