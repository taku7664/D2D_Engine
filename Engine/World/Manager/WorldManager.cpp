#include "pch.h"
#include "WorldManager.h"

World*				 WorldManager::m_activeWorld = nullptr;
std::vector<World*>  WorldManager::m_WorldList[(int)LayerTag::SIZE]{};

void WorldManager::Release()
{
	for (int i = 0; i < (int)LayerTag::SIZE; i++)
	{
		for (World* World : m_WorldList[i])
		{
			delete World;
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


bool WorldManager::LoadWorld(World* _World)
{
	if (_World == nullptr) return false;
	if (m_activeWorld && m_activeWorld == _World) return false;
	else
	{
		if (m_activeWorld)
			m_activeWorld->WorldExit();
		m_activeWorld = _World;
		m_activeWorld->WorldEnter();
		return true;
	}
}

bool WorldManager::LoadWorld(std::string _key, WorldTag _tag)
{
	if (m_activeWorld && m_activeWorld->GetName() == _key) return false;
	for (int i = 0; i < m_WorldList[(int)_tag].size(); i++)
	{
		if (m_WorldList[(int)_tag][i]->GetName() == _key)
		{
			if (m_activeWorld)
				m_activeWorld->WorldExit();
			m_activeWorld = m_WorldList[(int)_tag][i];
			m_activeWorld->WorldEnter();
			return true;
		}
	}
	return false;
}
