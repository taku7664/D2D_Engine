#pragma once
#include "../Sprite2D.h"
#include "../Animation2D.h"

class ResourceManager
{
public:

	template <typename T>
	static T* GetResource(const std::wstring& key)
	{
		auto it = m_resourceMap.find(key);

		if (it != m_resourceMap.end())
		{
			return dynamic_cast<T*>(it->second);
		}
		return nullptr;
	} 

	static Resource::Sprite2D*  AddSprite2D(const std::wstring& _path, SpriteData _data = SpriteData());
	static Resource::Sprite2D*  AddAnimation2DFromCSV(const std::wstring& _name, Resource::Sprite2D* _sprite, const std::wstring& _csvPath);

	static void SetParentPath(std::wstring _path) { m_parentPath = _path; }

	static void Clear();

private:

	/*static std::map<std::wstring, Resource::Texture2D*> m_textureMap;
	static std::map<std::wstring, Resource::Sprite2D*> m_spriteMap;*/

	static std::wstring m_parentPath;
	static std::unordered_map<std::wstring, Resource::Sprite2D*> m_resourceMap;
	static std::unordered_map<std::wstring, Resource::Sprite2D*> m_animationMap;

};
