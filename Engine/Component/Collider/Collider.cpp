#include "pch.h"
#include "Collider.h"
#include "../../World/Object/Actor/Actor.h"

UINT Collider::CollisionID = 1;

Collider::Collider()
	: isTrigger(false),
	m_id(CollisionID++)
{
}

Collider::~Collider()
{

}

void Collider::OnCollisionEnter(Actor* other)
{
	m_color = D2D1::ColorF(D2D1::ColorF::LightGreen);
	for (Component*& comp : gameObject->GetComponentList(ComponentType::Script))
	{
		if (comp->GetType() == ComponentType::Script && comp->GetState() == GameState::Active)
		{
			dynamic_cast<Script*>(comp)->OnCollisionEnter(other);
		}
	}
}

void Collider::OnCollisionStay(Actor* other)
{
	m_color = D2D1::ColorF(D2D1::ColorF::Red);
	for (Component*& comp : gameObject->GetComponentList(ComponentType::Script))
	{
		if (comp->GetType() == ComponentType::Script && comp->GetState() == GameState::Active)
		{
			dynamic_cast<Script*>(comp)->OnCollisionStay(other);
		}
	}
}

void Collider::OnCollisionExit(Actor* other)
{
	m_color = D2D1::ColorF(D2D1::ColorF::LightGreen);
	for (Component*& comp : gameObject->GetComponentList(ComponentType::Script))
	{
		if (comp->GetType() == ComponentType::Script && comp->GetState() == GameState::Active)
		{
			dynamic_cast<Script*>(comp)->OnCollisionExit(other);
		}
	}
}
