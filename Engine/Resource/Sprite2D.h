#pragma once
#include "Resource2D.h"

struct SpriteData
{
	D2D_VECTOR_2F cut_by_grid;
	D2D_VECTOR_2F margin;
	D2D_RECT_F    offset;

	SpriteData(
		D2D_VECTOR_2F _grid = { 1,1 },
		D2D_VECTOR_2F _margin = { 0,0 },
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

		std::vector<ID2D1Bitmap*> m_spriteSheet; // ��������Ʈ �����͸� ���� �ڸ� ��������Ʈ
		SpriteData m_spriteData;				 // ��������Ʈ �̹����� �ڸ� ����

	};
}

