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
		, ObjectTag _tag = ObjectTag::Defalut)
	{
		T* obj = new T(_name, _tag);
		obj->SetLayerOwner(m_layers[(int)_type]);
		m_layers[(int)_type]->GetObjectList().push_back(obj);
		return obj;
	}

	template <typename T>
	T* FindObject(std::string _name, LayerTag _tag = LayerTag::Defalut)
	{
		T* temp;
		for (int i = (int)_tag; i < (int)LayerTag::SIZE; i++)
		{
			for (Object* obj : m_layers[i]->GetObjectList())
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

	std::string		 GetName()const { return m_WorldName; }
	WorldTag		 GetTag()const { return m_WorldTag; }
	Layer**			 GetLayerList() { return m_layers; }
	void			 SetName(std::string _name) { m_WorldName = _name; }
	void			 SetTag(WorldTag _tag) { m_WorldTag = _tag; }

private:

	std::string		 m_WorldName;
	WorldTag		 m_WorldTag;		 
	Layer*			 m_layers[(int)LayerTag::SIZE];

};