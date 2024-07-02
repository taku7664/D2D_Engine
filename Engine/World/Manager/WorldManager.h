#pragma once
#include "../World.h"

class WorldManager
{
public:

	static void Release();

	static void FixedUpdate();
	static void EarlyUpdate();
	static void Update();
	static void LateUpdate();
	static void Render();
	static void StateUpdate();

	// World을 추가한 후 World* 타입을 반환합니다.
	template <typename T>
	static T* CreateWorld(std::string _key, WorldTag _tag)
	{
		T* _World = new T();
		_World->SetName(_key);
		_World->SetTag(_tag);
		_World->WorldLoad();
		m_WorldList[(int)_tag].push_back(_World);
		if (!m_activeWorld) m_activeWorld = _World;
		return _World;
	}
	// World을 검색합니다.
	static World* FindWorld(std::string _key, WorldTag _tag = WorldTag::Default)
	{
		for (int i = (int)_tag; i < (int)WorldTag::SIZE; i++)
		{
			for (int j = 0; j < m_WorldList[i].size(); j++)
			{
				if (m_WorldList[i][j]->GetName() == _key)
					return m_WorldList[i][j];
			}
		}
		return nullptr;
	}
	// 해당 World을 삭제합니다.
	static bool DestroyWorld(std::string _key, WorldTag _tag = WorldTag::Default)
	{
		for (int i = (int)_tag; i < (int)WorldTag::SIZE; i++)
		{
			for (int j = 0; j < m_WorldList[i].size(); j++)
			{
				if (m_WorldList[i][j]->GetName() == _key)
				{
					m_WorldList[i][j]->WorldDestroy();
					delete m_WorldList[i][j];
					m_WorldList[i].erase(m_WorldList->begin() + j);
					return m_WorldList[i][j];
				}
			}
		}
		return false;
	}

	static bool LoadWorld(World* _World);
	static bool LoadWorld(std::string _key, WorldTag _tag = WorldTag::Default);

	static World* GetActiveWorld() { return m_activeWorld; }
	static std::vector<World*>& GetWorldList(WorldTag _tag) { return m_WorldList[(int)_tag]; }

private:

	static World* m_activeWorld;
	static std::vector<World*> m_WorldList[(int)LayerType::SIZE];
};

