#include "MainTitle.h"

void MainTitle::WorldLoad()
{
	CollisionManager::SetCollsionLayer(LayerTag::Player, true);
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
		clone = CreateObject<Actor>("Background", LayerTag::Defalut, ObjectTag::Defalut);
		clone->transform->position = { 100, 200 };
		SpriteRenderer2D* sp = clone->AddComponent<SpriteRenderer2D>();
		sp->bitmap = ResourceManager::GetSprite2D(L"S_BackGroud")->GetSprite();
	}
	// �ִϸ��̼� �׽�Ʈ�� ĳ����
	{
		clone = CreateObject<Actor>("Charactor1", LayerTag::Player, ObjectTag::Defalut);
		clone->AddComponent<TestScript>();
		clone->transform->position = { 100, 300 };
		Animator2D* ani = clone->AddComponent<Animator2D>();
		ani->AddAnimation("Idle", ResourceManager::GetAnimation2D(L"A_Idle"));
		ani->ActiveAnimation("Idle");
		RectRenderer* rect = clone->AddComponent<RectRenderer>();
		rect->size = ani->GetActiveAnimation()->GetSprite()->GetSize();
		rect->SetFill(false);
	}
	// �ִϸ��̼� �׽�Ʈ�� ĳ����
	{
		clone = CreateObject<Actor>("Charactor2", LayerTag::Player, ObjectTag::Defalut);
		clone->transform->position = { 50, 200 };
		clone->transform->SetParent(FindObject<Actor>("Charactor1")->transform);
		clone->depthsLevel = clone->transform->position.y;
		Animator2D* ani = clone->AddComponent<Animator2D>();
		ani->AddAnimation("Idle", ResourceManager::GetAnimation2D(L"A_Idle"));
		ani->ActiveAnimation("Idle");
		RectRenderer* rect = clone->AddComponent<RectRenderer>();
		rect->size = ani->GetActiveAnimation()->GetSprite()->GetSize();
		rect->SetFill(false);
	}
	// ī�޶� ������Ʈ �׽�Ʈ�� ���� ī�޶� ������Ʈ
	// �̷��� �� ����ī�޶� + ����ī�޶�� �� ȭ�鿡 2�밡 �ִ�.
	{
		clone = CreateObject<Actor>("SubCamera", LayerTag::Defalut, ObjectTag::Camera);
		clone->AddComponent<CameraController>();
		Camera2D* ca = clone->AddComponent<Camera2D>();
		ca->SetBackGroundColor(D2D1::ColorF(D2D1::ColorF::Gray));
		ca->viewportPosition = { 500, 50 };
		ca->viewportSize = { 400, 200 };
	}
	{
		clone = CreateObject<Actor>("Extra1", LayerTag::Player, ObjectTag::Camera);
		clone = CreateObject<Actor>("Extra2", LayerTag::Player, ObjectTag::Camera);
		clone = CreateObject<Actor>("Extra3", LayerTag::Player, ObjectTag::Camera);
		clone = CreateObject<Actor>("Extra4", LayerTag::Player, ObjectTag::Camera);
		clone = CreateObject<Actor>("Extra5", LayerTag::Player, ObjectTag::Camera);
		clone = CreateObject<Actor>("Extra6", LayerTag::Player, ObjectTag::Camera);
		clone = CreateObject<Actor>("Extra7", LayerTag::Player, ObjectTag::Camera);
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
