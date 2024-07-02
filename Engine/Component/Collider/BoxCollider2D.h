#pragma once
#include "Collider.h"

class BoxCollider2D
	: public Collider
{
public:

	BoxCollider2D();
	~BoxCollider2D();

	D2D1_SIZE_F size;

private:

};

