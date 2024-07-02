#pragma once
#include "../Object.h"

class Object;

class Widget abstract
	: public Object
{
public:

	Widget(std::string _name, ObjectTag _tag);
	virtual ~Widget();

private:

};

