#include "DemoApp.h"

void DemoApp::Initialize(HINSTANCE _hinstance, int _width, int _height, const wchar_t* _title)
{
	__super::Initialize(_hinstance, _width, _height, _title);
	LoadScene();
}

void DemoApp::LoadScene()
{
	SceneManager::CreateScene<MainTitle>("Title", SceneTag::Title);
	SceneManager::LoadScene("Title");
}

