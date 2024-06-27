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
	// Destroy���¸� ���ٲٰ� �ϱ� ���� PASS
	if (m_state == GameState::Destroy) return;

	GameState temp = _val ? GameState::Active : GameState::Passive;
	// ���� ���¿� ������ PASS
	if (m_state == temp) return;

	m_state = temp;

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

void Object::SetDestroy()
{
	// �̹� �������¸� PASS
	if (m_state == GameState::Destroy) return;

	m_state = GameState::Destroy;

	// ���� �����ϰ� �Լ��� ���� ����� ��������� ȣ��
	CallOnDestroy();
}

void Object::CallOnEnalbe()
{
	// Active������ �ڽĵ� ���� OnEnable�Լ��� ȣ�� 
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
	// CallOnEnalbe�� �Ȱ��� �۵�. (Passive������ �ֵ��� ���δ°� �´µ�?)
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
	// �ڽĵ� �߿� �̹� Destroy�� ���� OnDestroy�� ȣ�� �Ǿ��� ���̹Ƿ� Destroy���°� �ƴѰ͸� ȣ��
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

