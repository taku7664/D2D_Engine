#include "pch.h"
#include "DynamicText.h"

DynamicText::DynamicText(std::string _name, ObjectTag _tag)
	: Widget(_name, _tag)
{
	m_type = ObjectType::DynamicText;
}

DynamicText::~DynamicText()
{
}
