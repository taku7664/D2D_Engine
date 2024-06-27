#pragma once
#include "Renderer.h"
#include "../../Resource/Animation2D.h"

class AnimationRenderer
	: public Renderer
{
public:

	AnimationRenderer();
	~AnimationRenderer();

	virtual void Update() final;
	virtual void Draw(Camera2D* _camera) final;

	int GetFrame();
	void GotoAndPlay(int _val);
	void GotoAndStop(int _val);
	void Play();
	void Stop();
	bool End();
	bool IsLoop() { return isLoop; }

	int currentFrame;

private:

	std::map<std::wstring, Resource::Animation2D*> m_animationList;
	Resource::Animation2D* m_activeAnimation;
	bool isLoop;
	bool isStop;
	float m_frameCount;
};

