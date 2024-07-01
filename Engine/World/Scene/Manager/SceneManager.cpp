#include "pch.h"
#include "SceneManager.h"

Scene*				 SceneManager::m_activeScene = nullptr;
std::vector<Scene*>  SceneManager::m_sceneList[(int)LayerType::SIZE]{};

void SceneManager::Release()
{
	for (int i = 0; i < (int)LayerType::SIZE; i++)
	{
		for (Scene* scene : m_sceneList[i])
		{
			delete scene;
		}
	}
}

void SceneManager::FixedUpdate()
{
	if (m_activeScene)
		m_activeScene->FixedUpdate();
}

void SceneManager::EarlyUpdate()
{
	if (m_activeScene)
		m_activeScene->EarlyUpdate();
}

void SceneManager::Update()
{
	if (m_activeScene)
		m_activeScene->Update();
}

void SceneManager::LateUpdate()
{
	if (m_activeScene)
		m_activeScene->LateUpdate();
}

void SceneManager::Render()
{
	if (m_activeScene)
		m_activeScene->Render();
}

void SceneManager::StateUpdate()
{
	if (m_activeScene)
		m_activeScene->StateUpdate();
}


bool SceneManager::LoadScene(Scene* _scene)
{
	if (_scene == nullptr) return false;
	if (m_activeScene && m_activeScene == _scene) return false;
	else
	{
		if (m_activeScene)
			m_activeScene->SceneExit();
		m_activeScene = _scene;
		m_activeScene->SceneEnter();
		return true;
	}
}

bool SceneManager::LoadScene(std::string _key, SceneTag _tag)
{
	if (m_activeScene && m_activeScene->GetName() == _key) return false;
	for (int i = 0; i < m_sceneList[(int)_tag].size(); i++)
	{
		if (m_sceneList[(int)_tag][i]->GetName() == _key)
		{
			if (m_activeScene)
				m_activeScene->SceneExit();
			m_activeScene = m_sceneList[(int)_tag][i];
			m_activeScene->SceneEnter();
			return true;
		}
	}
	return false;
}
