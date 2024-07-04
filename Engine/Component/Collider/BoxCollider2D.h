#pragma once
#include "Collider.h"

class BoxCollider2D
	: public Collider
{
public:

	BoxCollider2D();
	~BoxCollider2D();

	virtual bool Draw(Camera2D* _camera) final;

	D2D1_SIZE_F size;

private:

};

