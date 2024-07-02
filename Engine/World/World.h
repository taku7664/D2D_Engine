#pragma once
#include "../World/Layer/Layer.h"

class Object;
class Layer;
class Actor;

class World
{
public:

	World();
	~World();

	static void Release();

	void FixedUpdate();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void StateUpdate();
	void Render();

	virtual void WorldLoad() {}
	virtual void WorldDestroy() {}
	virtual void WorldEnter() {}
	virtual void WorldExit() {}

	template <typename T>
	T* CreateObject(std::string _name = ""
		, LayerTag _type = LayerTag::Defalut
		, ObjectTag _tag = ObjectTag::Defalut
		, bool _isPersistent = false)
	{
		T* obj = new T(_name, _tag);
		if (_isPersistent)
		{
			obj->SetLayerOwner(m_persistentLayers[(int)_type]);
			m_persistentLayers[(int)_type]->GetObjectList().push_back(obj);
		}
		else
		{
			obj->SetLayerOwner(m_layers[(int)_type]);
			m_layers[(int)_type]->GetObjectList().push_back(obj);
		}
		return obj;
	}

	template <typename T>
	T* FindObject(std::string _name)
	{
		T* temp;
		for (int i = 0; i < (int)LayerTag::SIZE; i++)
		{
			for (Object* obj : m_persistentLayers[i])
			{
				if (obj->GetName() == _name)
				{
					if (temp = dynamic_cast<T*>(obj))
						return temp;
				}
			}
			for (Object* obj : m_layers[i])
			{
				if (obj->GetName() == _name)
				{
					if (temp = dynamic_cast<T*>(obj))
						return temp;
				}
			}
		}
		return nullptr;
	}

	std::string  GetName()const { return m_WorldName; }
	WorldTag	 GetTag()const { return m_WorldTag; }
	Layer**		 GetLayerList() { return m_layers; }
	static Layer**	GetPersistentLayers() { return m_persistentLayers; }
	void		 SetName(std::string _name) { m_WorldName = _name; }
	void		 SetTag(WorldTag _tag) { m_WorldTag = _tag; }

private:

	std::string   m_WorldName;
	WorldTag      m_WorldTag;

	Layer*		  m_layers[(int)LayerTag::SIZE];
	static Layer* m_persistentLayers[(int)LayerTag::SIZE];

};