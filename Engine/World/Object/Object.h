#pragma once
#include "../../Component/Transform2D.h"

class Layer;

class Object abstract
{
public:

	Object(std::string _name, ObjectTag _tag = ObjectTag::Defalut);
	virtual ~Object();

	virtual void		FixedUpdate();
	virtual void		EarlyUpdate();
	virtual void		Update();
	virtual void		LateUpdate();
	virtual void		Draw(Camera2D* _camera);
	virtual void		Render();

	virtual void		SetActive(bool _val);
	virtual void		SetDestroy();
	void		        SetState(GameState _state) { m_state = _state; }
	void                SetLayerOwner(Layer* _layer) { m_ownerLayer = _layer; }
	void                SetPersistent(bool _isPersistent) { isPersistent = _isPersistent; }
	Layer*		        GetLayerOwner() { return m_ownerLayer; }
	std::string         GetName() { return m_name; }
	ObjectTag	        GetTag() { return m_tag; }
	ObjectType          GetType() { return m_type; }
	GameState	        GetState() { return m_state; }
	bool                IsPersistent() { return isPersistent; }

	Transform2D*        transform;
	// 정수 비교와 부동소수점 비교시간의 차이를 테스트해봣으나 거의 별 차이가 없었음.
	float				depthsLevel;

protected:

	bool                isPersistent;
					    
	Layer*		        m_ownerLayer;
	std::string		    m_name;
	ObjectTag		    m_tag;
	ObjectType		    m_type;
	GameState		    m_state;
};

