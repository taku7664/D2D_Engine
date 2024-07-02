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
	// ������Ʈ �Ҵ� ����
	for (int i = 0; i < (int)ComponentType::SIZE; i++)
	{
		for (Component*& comp : m_componentList[i]) {
			delete comp;
		}
	}
	// �ڽĿ�����Ʈ �Ҵ� ����
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

	// �ڽĵ鵵 ȣ���ؾ� �ϱ� ������ �Լ��� ���� ���� ��������� ȣ��
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
	// Active������ �ڽĵ� ���� OnEnable�Լ��� ȣ�� 
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
	// CallOnEnalbe�� �Ȱ��� �۵�. (Passive������ �ֵ��� ���δ°� �´µ�?)
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
	// �ڽĵ� �߿� �̹� Destroy�� ���� OnDestroy�� ȣ�� �Ǿ��� ���̹Ƿ� Destroy���°� �ƴѰ͸� ȣ��
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
