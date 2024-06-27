#pragma once
#include "../Scene.h"

class SceneManager
{
public:

	static void FixedUpdate();
	static void EarlyUpdate();
	static void Update();
	static void LateUpdate();
	static void Render();
	static void StateUpdate();

	// Scene�� �߰��� �� Scene* Ÿ���� ��ȯ�մϴ�.
	template <typename T>
	static T* CreateScene(std::string _key, SceneTag _tag)
	{
		T* _scene = new T();
		_scene->SetName(_key);
		_scene->SetTag(_tag);
		_scene->SceneLoad();
		m_sceneList[(int)_tag].push_back(_scene);
		if (!m_activeScene) m_activeScene = _scene;
		return _scene;
	}
	// Scene�� �˻��մϴ�.
	static Scene* FindScene(std::string _key, SceneTag _tag = SceneTag::Default)
	{
		for (int i = (int)_tag; i < (int)SceneTag::SIZE; i++)
		{
			for (int j = 0; j < m_sceneList[i].size(); j++)
			{
				if (m_sceneList[i][j]->GetName() == _key)
					return m_sceneList[i][j];
			}
		}
		return nullptr;
	}
	// �ش� Scene�� �����մϴ�.
	static bool DestroyScene(std::string _key, SceneTag _tag = SceneTag::Default)
	{
		for (int i = (int)_tag; i < (int)SceneTag::SIZE; i++)
		{
			for (int j = 0; j < m_sceneList[i].size(); j++)
			{
				if (m_sceneList[i][j]->GetName() == _key)
				{
					m_sceneList[i][j]->SceneDestroy();
					delete m_sceneList[i][j];
					m_sceneList[i].erase(m_sceneList->begin() + j);
					return m_sceneList[i][j];
				}
			}
		}
		return false;
	}

	static bool LoadScene(Scene* _scene);
	static bool LoadScene(std::string _key, SceneTag _tag = SceneTag::Default);

	static Scene* GetActiveScene() { return m_activeScene; }
	static std::vector<Scene*>& GetSceneList(SceneTag _tag) { return m_sceneList[(int)_tag]; }

private:

	static Scene* m_activeScene;
	static std::vector<Scene*> m_sceneList[(int)LayerType::SIZE];
};

