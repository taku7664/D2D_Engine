#pragma once

enum class GameState
{
	Create,
	Active,
	Passive,
	Destroy,
};

enum class SceneTag
{
	Default,
	Load,
	Title,
	Play,
	SIZE,
};

enum class LayerType
{
	Defalut,
	Tile,
	Monster,
	Player,
	Particle,
	UI,
	SIZE,
};

enum class ObjectTag
{
	Defalut,
	Player,
	Object,
	Camera,
	Monster,
	SIZE,
};

enum class ComponentType
{
	Transform2D,
	TextureRenderer,
	SpriteRenderer2D,
	AnimationRenderer,
	Camera,
	Script,
	SIZE,
};

enum class ResourceType
{
	NONE,
	Texture2D,
	Sprite2D,
	Animation2D,
	SIZE,
};

enum class KeyType // 키보드
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,
	SPACEBAR = VK_SPACE,
};

enum class MouseType // 마우스
{
	LEFT = VK_LBUTTON,
	ROLL = VK_MBUTTON,
	RIGHT = VK_RBUTTON,
};