#include "pch.h"
#include "Actor.h"

Actor::Actor(std::string _name, ObjectTag _tag)
	: Object(_name, _tag)
{
	m_type = ObjectType::Actor;
	m_componentList->clear();
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
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnEnable();
	}
}

void Actor::CallOnDisalbe()
{
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnDisable();
	}
}

void Actor::CallOnDestroy()
{
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnDestroy();
	}
}
