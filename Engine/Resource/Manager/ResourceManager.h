#pragma once
#include "../Sprite2D.h"
#include "../Animation2D.h"

class ResourceManager
{
public:

	static Resource::Sprite2D*  AddSprite2D(const std::wstring& _key ,const std::wstring& _path, SpriteData _data = SpriteData());
	static Resource::Animation2D*  AddAnimation2D(const std::wstring& _key, Resource::Sprite2D* _sprite, std::vector<AnimationData>& _data);

	static Resource::Sprite2D* GetSprite2D(const std::wstring& _key);
	static Resource::Animation2D* GetAnimation2D(const std::wstring& _key);

	// Asset폴더 기본 경로 지정
	static void SetAssetPath(std::wstring _path) { m_assetPath = _path; }

	static void Clear() {}

private:

	static std::wstring m_assetPath;
	static std::unordered_map<std::wstring, Resource::Sprite2D*> m_spriteMap;
	static std::unordered_map<std::wstring, Resource::Animation2D*> m_animationMap;

};
