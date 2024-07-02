#include "MainTitle.h"

void MainTitle::WorldLoad()
{
	{
		// ��� ��¿� �ӽ� ���ҽ� ����
		ResourceManager::AddSprite2D(L"S_BackGroud", L"bg.png");
		// �ִϸ��̼� ��¿� �ӽ� ���ҽ� ����
		ResourceManager::AddSprite2D(L"S_Idle", L"3.png", SpriteData({ 5,5 }));
		std::vector<AnimationData> arr = {
			{0, 0.1f},
			{1, 0.1f},
			{2, 0.1f},
			{3, 0.1f},
			{4, 0.1f},
			{5, 0.1f},
			{6, 0.1f},
			{7, 0.1f},
			{8, 0.1f},
		};
		ResourceManager::AddAnimation2D(L"A_Idle", ResourceManager::GetSprite2D(L"S_Idle"), arr);
	}
	
	Actor* clone;
	// ��������Ʈ ��¿� ���
	{
		clone = CreateObject<Actor>("Background", LayerType::Defalut, ObjectTag::Defalut);
		clone->transform->position = { 100, 200 };
		SpriteRenderer2D* sp = clone->AddComponent<SpriteRenderer2D>();
		sp->bitmap = ResourceManager::GetSprite2D(L"S_BackGroud")->GetSprite();
	}
	// �ִϸ��̼� �׽�Ʈ�� ĳ����
	{
		clone = CreateObject<Actor>();
		clone->AddComponent<TestScript>();
		clone->transform->position = { 100, 200 };
		Animator2D* ani = clone->AddComponent<Animator2D>();
		ani->AddAnimation("Idle", ResourceManager::GetAnimation2D(L"A_Idle"));
		ani->ActiveAnimation("Idle");
	}
	// ī�޶� ������Ʈ �׽�Ʈ�� ���� ī�޶� ������Ʈ
	// �̷��� �� ����ī�޶� + ����ī�޶�� �� ȭ�鿡 2�밡 �ִ�.
	{
		clone = CreateObject<Actor>("SubCamera", LayerType::Defalut, ObjectTag::Camera);
		clone->AddComponent<CameraController>();
		Camera2D* ca = clone->AddComponent<Camera2D>();
		ca->SetBackGroundColor(D2D1::ColorF(D2D1::ColorF::Gray));
		ca->viewportPosition = { 500, 50 };
		ca->viewportSize = { 400, 200 };
	}
}

void MainTitle::WorldDestroy()
{
}

void MainTitle::WorldEnter()
{
}

void MainTitle::WorldExit()
{
}
