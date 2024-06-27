#include "pch.h"
#include "ResourceManager.h"

std::wstring							      ResourceManager::m_parentPath = L"Asset/";
std::unordered_map<std::wstring, Resource::Sprite2D*> ResourceManager::m_resourceMap;

Resource::Sprite2D* ResourceManager::AddSprite2D(const std::wstring& _path, SpriteData _data)
{
	std::wstring temp = m_parentPath + _path;
	Resource::Sprite2D* _sprite = GetResource<Resource::Sprite2D>(temp);
	if (_sprite != nullptr)
	{
		return _sprite;
	}
	else
	{
		_sprite = new Resource::Sprite2D(temp, _data);
		m_resourceMap.insert(std::make_pair(_path, _sprite));
	}
	return _sprite;
}

Resource::Sprite2D* ResourceManager::AddAnimation2DFromCSV(const std::wstring& _name, Resource::Sprite2D* _sprite, const std::wstring& _csvPath)
{
	return nullptr;
}