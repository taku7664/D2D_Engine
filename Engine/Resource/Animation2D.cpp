#include "pch.h"
#include "Animation2D.h"

Resource::Animation2D::Animation2D(std::wstring _key, Sprite2D* _sprite, std::vector<AnimationData>& _data)
{
	m_key = _key;
	type = ResourceType::Animation2D;
	m_sprite = _sprite;

	m_frameData = _data;
}

Resource::Animation2D::~Animation2D()
{
}
