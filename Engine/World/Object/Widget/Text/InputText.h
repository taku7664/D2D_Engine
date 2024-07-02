#pragma once
#include "../Widget.h"

class Widget;

class InputText
	: public Widget
{
public:
	InputText(std::string _name, ObjectTag _tag);
	virtual ~InputText();
private:

};