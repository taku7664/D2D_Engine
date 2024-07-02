#include "pch.h"
#include "Actor.h"

Actor::Actor(std::string _name, ObjectTag _tag)
	: Object(_name, _tag)
{
	m_componentList->clear();
	m_child.clear();
	transform = this->AddComponent<Transform2D>();
}

Actor::~Actor()
{
	// 컴포넌트 할당 해제
	for (int i = 0; i < (int)ComponentType::SIZE; i++)
	{
		for (Component*& comp : m_componentList[i]) {
			delete comp;
		}
	}
	// 자식오브젝트 할당 해제
	for (Object*& child : m_child) {
		delete child;
	}
}

void Actor::FixedUpdate()
{
	for (int i = 0; i < (int)ComponentType::SIZE; i++)
	{
		for (Component*& comp : m_componentList[i])
		{
			if (comp)
				comp->FixedUpdate();
		}
	}
	for (Object*& child : m_child)
	{
		if (child->GetState() == GameState::Active)
			child->FixedUpdate();
	}
}

void Actor::EarlyUpdate()
{
	for (int i = 0; i < (int)ComponentType::SIZE; i++)
	{
		for (Component*& comp : m_componentList[i])
		{
			if (comp)
				comp->EarlyUpdate();
		}
	}
	for (Object*& child : m_child)
	{
		if (child->GetState() == GameState::Active)
			child->EarlyUpdate();
	}
}

void Actor::Update()
{
	for (int i = 0; i < (int)ComponentType::SIZE; i++)
	{
		for (Component*& comp : m_componentList[i])
		{
			if (comp)
				comp->Update();
		}
	}
	for (Object*& child : m_child)
	{
		if (child->GetState() == GameState::Active)
			child->Update();
	}
}

void Actor::LateUpdate()
{
	for (int i = 0; i < (int)ComponentType::SIZE; i++)
	{
		for (Component*& comp : m_componentList[i])
		{
			if (comp)
				comp->LateUpdate();
		}
	}
	for (Object*& child : m_child)
	{
		if (child->GetState() == GameState::Active)
			child->LateUpdate();
	}
}

void Actor::Draw(Camera2D* _camera)
{
	for (int i = 0; i < (int)ComponentType::SIZE; i++)
	{
		for (Component*& comp : m_componentList[i])
		{
			if (comp)
				comp->Draw(_camera);
		}
	}
	for (Object*& child : m_child)
	{
		if (child->GetState() == GameState::Active)
			child->Draw(_camera);
	}
}

void Actor::Render()
{
	for (int i = 0; i < (int)ComponentType::SIZE; i++)
	{
		for (Component*& comp : m_componentList[i])
		{
			if (comp)
				comp->Render();
		}
	}
	for (Object*& child : m_child)
	{
		if (child->GetState() == GameState::Active)
			child->Render();
	}
}

Actor* Actor::CreateChild(std::string _name, ObjectTag _tag)
{
	Actor* child = new Actor(_name, _tag);
	child->SetParent(this);
	m_child.push_back(child);
	return child;
}

void Actor::SetActive(bool _val)
{
	__super::SetActive(_val);

	// 자식들도 호출해야 하기 때문에 함수를 따로 만들어서 재귀적으로 호출
	if (m_state == GameState::Active)
	{
		CallOnEnalbe();
	}
	else if (m_state == GameState::Passive)
	{
		CallOnDisalbe();
	}
}

void Actor::SetDestroy()
{
	__super::SetDestroy();

	CallOnDestroy();
}

void Actor::CallOnEnalbe()
{
	// Active상태인 자식들 전부 OnEnable함수를 호출 
	for (Object*& child : m_child)
	{
		Actor* actor = dynamic_cast<Actor*>(child);
		if (actor && actor->GetState() == GameState::Active)
			actor->CallOnEnalbe();
	}
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnEnable();
	}
}

void Actor::CallOnDisalbe()
{
	// CallOnEnalbe과 똑같이 작동. (Passive상태인 애들은 냅두는게 맞는듯?)
	for (Object*& child : m_child)
	{
		Actor* actor = dynamic_cast<Actor*>(child);
		if (actor && child->GetState() == GameState::Active)
			actor->CallOnDisalbe();
	}
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnDisable();
	}
}

void Actor::CallOnDestroy()
{
	// 자식들 중에 이미 Destroy된 것은 OnDestroy가 호출 되었을 것이므로 Destroy상태가 아닌것만 호출
	for (Object*& child : m_child)
	{
		Actor* actor = dynamic_cast<Actor*>(child);
		if (actor && child->GetState() != GameState::Destroy)
			actor->CallOnDestroy();
	}
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnDestroy();
	}
}
