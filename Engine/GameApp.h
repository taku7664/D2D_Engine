#pragma once
#include "pch.h"
#include "Render/D2DRender.h"
#include "World/Manager/WorldManager.h"
#include "Resource/Manager/ResourceManager.h"
#include "Physics/Manager/CollisionManager.h"

// 최상단 인터페이스
// 클라이언트 측에서 GameApp을 include 및 상속해서 쓰면 모든 기능을 사용할 수 잇다.

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

