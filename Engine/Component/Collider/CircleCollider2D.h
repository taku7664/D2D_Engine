#pragma once
#include "Collider.h"

class CircleCollider2D 
	: public Collider
{
public:

	CircleCollider2D();
	~CircleCollider2D();

	float radius;

private:

};