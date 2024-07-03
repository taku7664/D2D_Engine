#pragma once
#include "Resource2D.h"

struct SpriteData
{
	Vector2		  cut_by_grid;
	Vector2	      margin;
	D2D_RECT_F    offset;

	SpriteData(
		Vector2 _grid = { 1,1 },
		Vector2 _margin = { 0,0 },
		D2D_RECT_F _offset = { 0,0,0,0 })
		: cut_by_grid(_grid),
		offset(_offset),
		margin(_margin) {}
};

namespace Resource
{
	class Sprite2D
		: public Resource2D
	{
	public:

		Sprite2D(const std::wstring& _path, SpriteData _data);
		virtual ~Sprite2D();

		ID2D1Bitmap* GetSprite(int _index = 0) 
		{
			return m_spriteSheet[_index];
		}

	protected:

		std::vector<ID2D1Bitmap*> m_spriteSheet; // 스프라이트 데이터를 토대로 자른 스프라이트
		SpriteData m_spriteData;				 // 스프라이트 이미지를 자를 기준

	};
}

