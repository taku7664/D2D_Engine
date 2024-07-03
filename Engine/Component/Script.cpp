#include "pch.h"
#include "Script.h"
#include "../World/Object/Object.h"

Script::Script()
{
	m_type = ComponentType::Script;
}

Script::~Script()
{
}

void Script::Destroy(Object* _object)
{
	_object->SetDestroy();
}

void Script::SetPersistentObject(Object* _obj, bool _isPersistent)
{
	_obj->SetPersistent(_isPersistent);
}

