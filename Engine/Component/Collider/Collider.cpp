#include "pch.h"
#include "Collider.h"

Collider::Collider()
	: isTrigger(false)
{

}

Collider::~Collider()
{

}

void Collider::Draw(Camera2D* _camera)
{
}

void Collider::OnCollisionEnter(Object* other)
{
	/*for (Component*& comp : m_owner->GetComponentList(ComponentType::Script))
	{
		if (comp->GetType() == ComponentType::Script && comp->GetState() == GameState::Active)
		{
			dynamic_cast<Script*>(comp)->OnCollisionEnter(other);
		}
	}*/
}

void Collider::OnCollisionStay(Object* other)
{
	/*for (Component*& comp : GetOwner()->GetComponentList())
	{
		if (comp->GetType() == ComponentType::Script && comp->GetState() == GameState::Active)
		{
			dynamic_cast<Script*>(comp)->OnCollisionStay(other);
		}
	}*/
}

void Collider::OnCollisionExit(Object* other)
{
	/*for (Component*& comp : GetOwner()->GetComponentList())
	{
		if (comp->GetType() == ComponentType::Script && comp->GetState() == GameState::Active)
		{
			dynamic_cast<Script*>(comp)->OnCollisionExit(other);
		}
	}*/
}
