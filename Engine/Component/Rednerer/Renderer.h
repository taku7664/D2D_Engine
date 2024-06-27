#pragma once
#include "../Component.h"

class Renderer abstract
	: public Component 
{
public:
	Renderer() = default;
	~Renderer() = default;

	virtual void Draw(Camera2D* _camera) {}

	D2D1_VECTOR_2F size = { 0,0 };
	D2D1_VECTOR_2F offset = { 0,0 };
	float alpha = 1.f;

};

