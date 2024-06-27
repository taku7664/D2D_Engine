#pragma once
#include "Renderer.h"
#include "../../Resource/Sprite2D.h"

class SpriteRenderer2D
	: public Renderer
{
public:
	SpriteRenderer2D();
	~SpriteRenderer2D();

	virtual void Draw(Camera2D* _camera) final;

	Resource::Sprite2D* sprite;
	ID2D1Bitmap* bitmap;

private: 

};

