#pragma once
#include "../Layer/Layer.h"

class Object;

class Scene
{
public:

	Scene();
	~Scene();

	void FixedUpdate();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void StateUpdate();
	void Render();

	virtual void SceneLoad() {}
	virtual void SceneDestroy() {}
	virtual void SceneEnter() {}
	virtual void SceneExit() {}

	Object*		 CreateObject(LayerType _type = LayerType::Defalut
		, ObjectTag _tag = ObjectTag::Defalut
		, std::string _name = "");

	Object*		 FindObject(std::wstring _key, LayerType _layer); // 특정 레이어만 검사합니다.
	Object*		 FindObject(std::wstring _key); // 모든 레이어를 검사합니다.

	void		 DontDestroyOnLoad(Object* _obj);

	std::string  GetName()const { return m_sceneName; }
	SceneTag	 GetTag()const { return m_sceneTag; }
	Layer**		 GetLayerList() { return m_layerList; }
	Layer**	     GetDontDestroyLayer() { return m_dontDestroyLayerList; }
	void		 SetName(std::string _name) { m_sceneName = _name; }
	void		 SetTag(SceneTag _tag) { m_sceneTag = _tag; }

private:

	std::string  m_sceneName;
	SceneTag     m_sceneTag;

	Layer* m_layerList[(int)LayerType::SIZE];
	static Layer* m_dontDestroyLayerList[(int)LayerType::SIZE];

};