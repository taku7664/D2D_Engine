#include "pch.h"
#include "GameApp.h"

void GameApp::Initialize(HINSTANCE _hinstance, int _width, int _height, const wchar_t* _title)
{
	HWND hwnd = InitializeWindow(_hinstance, _width, _height, _title);
	if (!hwnd)
		assert(false && "Fail - InitializeWindow");
	D2DRender::Initialize(hwnd);
	Time::Initialize();
}	

void GameApp::Run()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP)
			{
				Input::GetKey(msg);
			}
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Time::Update();
			Input::Update();
			FixedUpdate();
			EarlyUpdate();
			Update();
			LateUpdate();
			StateUpdate();
			Render();
			Input::ResetKey();
		}
	}
}

void GameApp::Release()
{
	D2DRender::Release();
	SceneManager::Release();
	Debug.Close_Console();
}

void GameApp::FixedUpdate()
{
	static float deltaCount;
	deltaCount += Time::deltaTime;
	while (deltaCount >= 0.02f)
	{
		SceneManager::FixedUpdate();
		deltaCount -= 0.02f;
	}
}

void GameApp::EarlyUpdate()
{
    Input::Update();
	SceneManager::EarlyUpdate();
}

void GameApp::Update()
{
	SceneManager::Update();
}

void GameApp::LateUpdate()
{
	SceneManager::LateUpdate();
	Input::ResetKey();
}

void GameApp::StateUpdate()
{
	SceneManager::StateUpdate();
}

void GameApp::Render()
{
	D2DRender::BeginDraw();
	SceneManager::Render();
	D2DRender::EndDraw();
}

HWND GameApp::InitializeWindow(HINSTANCE _hinstance, int _width, int _height, const wchar_t* _title)
{

	WNDCLASS WndC = {};
	WndC.style = CS_HREDRAW | CS_VREDRAW;
	WndC.lpfnWndProc = WndProc;
	WndC.cbClsExtra = 0;
	WndC.cbWndExtra = 0;
	WndC.hInstance = _hinstance;
	WndC.hIcon = LoadIcon(_hinstance, IDI_APPLICATION);
	WndC.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndC.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WndC.lpszMenuName = NULL;
	WndC.lpszClassName = _title;

	RegisterClass(&WndC);

	// 원하는 클라이언트 영역 크기
	RECT clientRect = { 0, 0, _width, _height };

	// 윈도우 스타일 지정 (메뉴 바 제외)
	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&clientRect, style, FALSE);

	int windowWidth = clientRect.right - clientRect.left;
	int windowHeight = clientRect.bottom - clientRect.top;

	HWND hwnd = CreateWindow(
		_title, _title, style,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
		NULL, NULL, _hinstance, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	return hwnd;
}

void GameApp::CenterOfScreen(HWND _hwnd)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT windowRect;
	GetWindowRect(_hwnd, &windowRect);

	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	SetWindowPos(_hwnd, NULL,
		(screenWidth - windowWidth) / 2,
		(screenHeight - windowHeight) / 2,
		0, 0, SWP_NOZORDER | SWP_NOSIZE
	);
}

LRESULT GameApp::WndProc(HWND _hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Alt 키 비활성화용
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		if (wParam == VK_MENU)
			return 0;
		break;
	case WM_CREATE:
	{
		// 윈도우를 화면 중앙으로 이동
		//CenterOfScreen(_hwnd);
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(_hwnd, message, wParam, lParam);
	}
	return 0;
}