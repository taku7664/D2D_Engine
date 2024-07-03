#include "pch.h"
#include "WorldManager.h"

World*				 WorldManager::m_activeWorld = nullptr;
std::vector<World*>  WorldManager::m_worldList[(int)LayerTag::SIZE]{};

void WorldManager::Release()
{
	for (int i = 0; i < (int)LayerTag::SIZE; i++)
	{
		for (World* world : m_worldList[i])
		{
			delete world;
		}
	}
	World::Release();
}

void WorldManager::FixedUpdate()
{
	if (m_activeWorld)
		m_activeWorld->FixedUpdate();
}

void WorldManager::EarlyUpdate()
{
	if (m_activeWorld)
		m_activeWorld->EarlyUpdate();
}

void WorldManager::Update()
{
	if (m_activeWorld)
		m_activeWorld->Update();
}

void WorldManager::LateUpdate()
{
	if (m_activeWorld)
		m_activeWorld->LateUpdate();
}

void WorldManager::Render()
{
	if (m_activeWorld)
		m_activeWorld->Render();
}

void WorldManager::StateUpdate()
{
	if (m_activeWorld)
		m_activeWorld->StateUpdate();
}


bool WorldManager::LoadWorld(World* _world)
{
	if (_world == nullptr) return false;
	if (m_activeWorld == _world) return false;
	else
	{
		if (m_activeWorld)
		{
			m_activeWorld->WorldExit();
			// Persistent객체를 옮겨준다.
			for (int i = 0; i < (int)LayerTag::SIZE; i++)
			{
				std::vector<Object*>& objList = m_activeWorld->GetLayerList()[i]->GetObjectList();
				for (auto iter = objList.begin(); iter != objList.end();)
				{
					if ((*iter)->IsPersistent())
					{
						_world->GetLayerList()[i]->GetObjectList().push_back((*iter));
						objList.erase(iter);
					}
					else
					{
						++iter;
					}
				}
			}
		}
		m_activeWorld = _world;
		m_activeWorld->WorldEnter();
		return true;
	}
}

bool WorldManager::LoadWorld(std::string _key, WorldTag _tag)
{
	World* find = FindWorld(_key, _tag);
	bool check = LoadWorld(find);
	return check;
}
