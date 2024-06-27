#include "pch.h"
#include "Object.h"


Object::Object(std::string _name, ObjectTag _tag)
	: m_name(_name),
	m_tag(_tag),
	m_state(GameState::Active)
{
	m_componentList->clear();
	m_child.clear();
	transform = this->AddComponent<Transform2D>();
}

Object::~Object()
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

void Object::FixedUpdate()
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

void Object::EarlyUpdate()
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

void Object::Update()
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

void Object::LateUpdate()
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

void Object::Draw(Camera2D* _camera)
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

void Object::Render()
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

Object* Object::CreateChild(std::string _name, ObjectTag _tag)
{
	Object* child = new Object(_name, _tag);
	child->SetParent(this);
	m_child.push_back(child);
	return child;
}

void Object::SetActive(bool _val)
{
	// Destroy상태면 못바꾸게 하기 위해 PASS
	if (m_state == GameState::Destroy) return;

	GameState temp = _val ? GameState::Active : GameState::Passive;
	// 지금 상태와 같으면 PASS
	if (m_state == temp) return;

	m_state = temp;

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

void Object::SetDestroy()
{
	// 이미 삭제상태면 PASS
	if (m_state == GameState::Destroy) return;

	m_state = GameState::Destroy;

	// 위와 동일하게 함수를 따로 만들어 재귀적으로 호출
	CallOnDestroy();
}

void Object::CallOnEnalbe()
{
	// Active상태인 자식들 전부 OnEnable함수를 호출 
	for (Object*& child : m_child)
	{
		if (child->GetState() == GameState::Active)
			child->CallOnEnalbe();
	}
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnEnable();
	}
}

void Object::CallOnDisalbe()
{
	// CallOnEnalbe과 똑같이 작동. (Passive상태인 애들은 냅두는게 맞는듯?)
	for (Object*& child : m_child)
	{
		if (child->GetState() == GameState::Active)
			child->CallOnDisalbe();
	}
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnDisable();
	}
}

void Object::CallOnDestroy()
{
	// 자식들 중에 이미 Destroy된 것은 OnDestroy가 호출 되었을 것이므로 Destroy상태가 아닌것만 호출
	for (Object*& child : m_child)
	{
		if (child->GetState() != GameState::Destroy)
			child->CallOnDestroy();
	}
	for (Component*& comp : m_componentList[(int)ComponentType::Script])
	{
		if (comp->GetState() == GameState::Active)
			dynamic_cast<Script*>(comp)->OnDestroy();
	}
}

