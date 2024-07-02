#include "MainTitle.h"

void MainTitle::WorldLoad()
{
	{
		// 배경 출력용 임시 리소스 생성
		ResourceManager::AddSprite2D(L"S_BackGroud", L"bg.png");
		// 애니메이션 출력용 임시 리소스 생성
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
	// 스프라이트 출력용 배경
	{
		clone = CreateObject<Actor>("Background", LayerTag::Defalut, ObjectTag::Defalut);
		clone->transform->position = { 100, 200 };
		clone->AddComponent<TestScript>();
		SpriteRenderer2D* sp = clone->AddComponent<SpriteRenderer2D>();
		sp->bitmap = ResourceManager::GetSprite2D(L"S_BackGroud")->GetSprite();
	}
	// 애니메이션 테스트용 캐릭터
	{
		clone = CreateObject<Actor>("Charactor");
		clone->AddComponent<TestScript>();
		clone->transform->position = { 100, 200 };
		Animator2D* ani = clone->AddComponent<Animator2D>();
		ani->AddAnimation("Idle", ResourceManager::GetAnimation2D(L"A_Idle"));
		ani->ActiveAnimation("Idle");
		RectRenderer* rect = clone->AddComponent<RectRenderer>();
		rect->size = ani->GetActiveAnimation()->GetSprite()->GetSize();
		rect->SetFill(false);
	}
	// 카메라 컴포넌트 테스트용 서브 카메라 오브젝트
	// 이러면 총 메인카메라 + 서브카메라로 총 화면에 2대가 있다.
	{
		clone = CreateObject<Actor>("SubCamera", LayerTag::Defalut, ObjectTag::Camera);
		clone->AddComponent<CameraController>();
		Camera2D* ca = clone->AddComponent<Camera2D>();
		ca->SetBackGroundColor(D2D1::ColorF(D2D1::ColorF::Gray));
		ca->viewportPosition = { 500, 50 };
		ca->viewportSize = { 400, 200 };
	}
	{
		clone = CreateObject<Actor>("1");
		clone = CreateObject<Actor>("２");
		clone = CreateObject<Actor>("３");
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
