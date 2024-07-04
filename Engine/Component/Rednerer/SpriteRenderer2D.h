#pragma once
#include "Renderer.h"
#include "../../Resource/Sprite2D.h"

class SpriteRenderer2D
	: public Renderer
{
public:
	SpriteRenderer2D();
	~SpriteRenderer2D();

	virtual bool Draw(Camera2D* _camera) final;

	ID2D1Bitmap* bitmap;

private: 

};

