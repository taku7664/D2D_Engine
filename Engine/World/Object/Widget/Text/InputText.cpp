#include "pch.h"
#include "InputText.h"

InputText::InputText(std::string _name, ObjectTag _tag)
	: Widget(_name, _tag)
{
	m_type = ObjectType::InputText;
}

InputText::~InputText()
{
}
