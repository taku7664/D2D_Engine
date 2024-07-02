#pragma once
#include "../../Component/Transform2D.h"

class Layer;

class Object
{
public:

	Object(std::string _name, ObjectTag _tag = ObjectTag::Defalut);
	virtual ~Object();

	virtual void FixedUpdate();
	virtual void EarlyUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw(Camera2D* _camera);
	virtual void Render();

	virtual void		SetActive(bool _val);
	virtual void		SetDestroy();
	void		SetState(GameState _state) { m_state = _state; }
	void		SetParent(Object* _parent) { m_parent = _parent; };
	void        SetLayerOwner(Layer* _layer) { m_ownerLayer = _layer; }
	ObjectTag	GetTag() { return m_tag; }
	std::string GetName() { return m_name; }
	Layer*      GetLayerOwner() { return m_ownerLayer; }
	GameState	GetState() { return m_state; }
	Object*     GetParent() { return m_parent; }

	Transform2D* transform;

protected:

	Object* m_parent;
	std::string m_name;
	ObjectTag m_tag;
	GameState m_state;

	Layer* m_ownerLayer;

};

