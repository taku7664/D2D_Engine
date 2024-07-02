#include "DemoApp.h"

void DemoApp::Initialize(HINSTANCE _hinstance, int _width, int _height, const wchar_t* _title)
{
	__super::Initialize(_hinstance, _width, _height, _title);
	LoadWorld();
}

void DemoApp::LoadWorld()
{
	WorldManager::CreateWorld<MainTitle>("Title", WorldTag::Title);
	WorldManager::LoadWorld("Title");
}

