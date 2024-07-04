#pragma once
#include "Renderer.h"
#include "../../Resource/Animation2D.h"

class Animator2D
	: public Renderer
{
public:

	Animator2D();
	~Animator2D();

	virtual void Update() final;
	virtual bool Draw(Camera2D* _camera) final;

	void AddAnimation(std::string _key, Resource::Animation2D* _ani);
	Resource::Animation2D* FindAnimation(const std::string& _key);
	void ActiveAnimation(const std::string& _key, bool _loop = true);
	Resource::Animation2D* GetActiveAnimation() { return m_activeAnimation; }

	void GotoAndPlay(int _val);
	void GotoAndStop(int _val);
	void Play();
	void Stop();
	bool End();
	bool IsLoop() { return isLoop; }

	int currentFrame;

private:

	std::map<std::string, Resource::Animation2D*> m_animationList;
	Resource::Animation2D* m_activeAnimation;
	bool isLoop;
	bool isStop;
	float m_frameCount;
};

