#pragma once

class Camera2D;
class Object;

class Component abstract
{
public:
	void			SetOwner(Object* _owner) { m_owner = _owner; }
	void			SetState(GameState _state) { m_state = _state; }
	Object*		    GetOwner() { return m_owner; }
	ComponentType	GetType() { return m_type; }
	GameState		GetState() { return m_state; }

	virtual void	Initialize() {}
	virtual void	Update() {}
	virtual void	FixedUpdate() {}
	virtual void	EarlyUpdate() {}
	virtual void    LateUpdate() {}
	virtual void	Draw(Camera2D* _camera) {}
	virtual void	Render() {}

protected:

	Object*         m_owner;
	ComponentType  	m_type;
	GameState	    m_state = GameState::Active;

};

