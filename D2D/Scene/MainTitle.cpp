#include "MainTitle.h"

void MainTitle::SceneLoad()
{
	ResourceManager::AddSprite2D(L"1.png");
	Object* clone = CreateObject();
	clone->AddComponent<TestScript>();
	clone->transform->position = { 100, 200 };
	SpriteRenderer2D* spr = clone->AddComponent<SpriteRenderer2D>();
	spr->bitmap = ResourceManager::GetResource<Resource::Sprite2D>(L"1.png")->GetSprite(0);

	{
		clone = CreateObject(LayerType::Defalut, ObjectTag::Camera, "SubCamera");
		Camera2D* ca = clone->AddComponent<Camera2D>();
		ca->SetBackGroundColor(D2D1::ColorF(D2D1::ColorF::Gray));
		ca->viewportPosition = { 500, 50 };
		ca->viewportSize = { 400, 200 };
	}
}

void MainTitle::SceneDestroy()
{
}

void MainTitle::SceneEnter()
{
}

void MainTitle::SceneExit()
{
}
