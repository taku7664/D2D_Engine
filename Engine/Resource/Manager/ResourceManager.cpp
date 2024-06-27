#include "pch.h"
#include "ResourceManager.h"

std::wstring ResourceManager::m_assetPath = L"Asset/";
std::unordered_map<std::wstring, Resource::Sprite2D*> ResourceManager::m_spriteMap;
std::unordered_map<std::wstring, Resource::Animation2D*> ResourceManager::m_animationMap;

Resource::Sprite2D* ResourceManager::AddSprite2D(const std::wstring& _key, const std::wstring& _path, SpriteData _data)
{
	std::wstring temp = m_assetPath + _path;
	Resource::Sprite2D* _sprite = GetSprite2D(_key);
	if (_sprite != nullptr)
	{
		return _sprite;
	}
	else
	{
		_sprite = new Resource::Sprite2D(temp, _data);
		m_spriteMap.insert(std::make_pair(_key, _sprite));
	}
	return _sprite;
}

Resource::Animation2D* ResourceManager::AddAnimation2D(const std::wstring& _key, Resource::Sprite2D* _sprite, std::vector<AnimationData>& _data)
{
	Resource::Animation2D* _anime = GetAnimation2D(_key);
	if (_anime != nullptr)
	{
		return _anime;
	}
	else
	{
		_anime = new Resource::Animation2D(_key, _sprite, _data);
		m_animationMap.insert(std::make_pair(_key, _anime));
	}
	return _anime;
}

Resource::Sprite2D* ResourceManager::GetSprite2D(const std::wstring& _key)
{
	auto it = m_spriteMap.find(_key);

	if (it == m_spriteMap.end())
		return nullptr;

	return it->second;
}

Resource::Animation2D* ResourceManager::GetAnimation2D(const std::wstring& _key)
{
	std::unordered_map<std::wstring, Resource::Animation2D*>::iterator it = m_animationMap.find(_key);

	if (it == m_animationMap.end())
		return nullptr;

	return it->second;
}
