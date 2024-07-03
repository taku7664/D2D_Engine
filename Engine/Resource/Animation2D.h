#pragma once
#include "Sprite2D.h"

struct AnimationData
{
	int index;
	float duration;
	Vector2 offset;
	AnimationData(int _index, float _duration, Vector2 _offset = { 0,0 })
		: index(_index), duration(_duration), offset(_offset) {}
};

namespace Resource
{
	class Animation2D
		: public Resource
	{
	public:
		Animation2D(std::wstring _key, Sprite2D* _sprite, std::vector<AnimationData>& _data);
		virtual ~Animation2D();
		std::vector<AnimationData>& GetFrameData() { return m_frameData; }
		ID2D1Bitmap* GetSprite(int _index = 0) { return m_sprite->GetSprite(_index); }
	private:
		Sprite2D* m_sprite;
		std::vector<AnimationData> m_frameData;
	};
}