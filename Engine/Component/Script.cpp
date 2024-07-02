#include "pch.h"
#include "Script.h"
#include "../World/Object/Object.h"

Script::Script()
{
	gameobject = nullptr;
	m_type = ComponentType::Script;
}

Script::~Script()
{
}

void Script::Destroy(Object* _World)
{
	_World->SetState(GameState::Destroy);
}