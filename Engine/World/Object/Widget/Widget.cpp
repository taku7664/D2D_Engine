#include "pch.h"
#include "Widget.h"

Widget::Widget(std::string _name, ObjectTag _tag)
	: Object(_name, _tag)
{
	transform = new Transform2D();
	transform->gameObject = this;
}

Widget::~Widget()
{
}
