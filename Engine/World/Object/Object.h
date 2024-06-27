#pragma once
#include "../../Component/Transform2D.h"
#include "../../Component/Camera2D.h"
#include "../../Component/Script.h"
#include "../../Component/Rednerer/SpriteRenderer2D.h"
#include "../../Component/Rednerer/AnimationRenderer.h"

class Component;
class Layer;

class Object
{
public:
	Object(std::string _name, ObjectTag _tag = ObjectTag::Defalut);
	~Object();

	void FixedUpdate();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Draw(Camera2D* _camera);
	void Render();

	Object* CreateChild(std::string _name, ObjectTag _tag = ObjectTag::Defalut);

	template <typename T>
	T* AddComponent()
	{
		T* temp = new T();
		temp->SetOwner(this);
		temp->Initialize();
		ComponentType type = temp->GetType();
		m_componentList[(int)type].push_back(temp);
		return temp;
	}

	template <typename T>
	T* GetComponent() {
		T* temp;
		for (int i = 0; i < (int)ComponentType::SIZE; i++)
		{
			for (Component* comp : m_componentList[i])
			{
				if (comp)
				{
					if (temp = dynamic_cast<T*>(comp))
						return temp;
				}
			}
		}
		return nullptr;
	}
	std::vector<Object*>& GetChild() { return m_child; };
	void		SetActive(bool _val);
	void		SetDestroy();
	void		SetState(GameState _state) { m_state = _state; }
	void		SetParent(Object* _parent) { m_parent = _parent; };
	void        SetLayerOwner(Layer* _layer) { m_ownerLayer = _layer; }
	ObjectTag	GetTag() { return m_tag; }
	std::string GetName() { return m_name; }
	Layer*      GetLayerOwner() { return m_ownerLayer; }
	GameState	GetState() { return m_state; }
	Object*     GetParent() { return m_parent; }

	Transform2D* transform;

private:

	ObjectTag m_tag;
	std::string m_name;
	GameState m_state;

	std::vector<Component*> m_componentList[(int)ComponentType::SIZE];

	Layer* m_ownerLayer;

	Object* m_parent;			 // 부모 Object
	std::vector<Object*> m_child; // 자식 Object

	void CallOnEnalbe();
	void CallOnDisalbe();
	void CallOnDestroy();

};

