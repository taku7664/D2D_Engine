#include "pch.h"
#include "Object.h"


Object::Object(std::string _name, ObjectTag _tag)
	: transform(nullptr),
	m_parent(nullptr),
	m_ownerLayer(nullptr),
	m_name(_name),
	m_tag(_tag),
	m_state(GameState::Active),
	depthsLevel(0)
{
}

Object::~Object()
{
}

void Object::FixedUpdate()
{
}

void Object::EarlyUpdate()
{
}

void Object::Update()
{
}

void Object::LateUpdate()
{
}

void Object::Draw(Camera2D* _camera)
{
}

void Object::Render()
{
}

void Object::SetActive(bool _val)
{
	// Destroy���¸� ���ٲٰ� �ϱ� ���� PASS
	if (m_state == GameState::Destroy) return;
	GameState temp = _val ? GameState::Active : GameState::Passive;
	// ���� ���¿� ������ PASS
	if (m_state == temp) return;
	m_state = temp;
}

void Object::SetDestroy()
{
	// �̹� �������¸� PASS
	if (m_state == GameState::Destroy) return;

	m_state = GameState::Destroy;
}


