#include "pch.h"
#include "AnimationRenderer.h"

AnimationRenderer::AnimationRenderer()
{
	m_type = ComponentType::AnimationRenderer;
	m_activeAnimation = nullptr;
	currentFrame = 0;
	isLoop = true;
	isStop = false;
	m_frameCount = 0.f;
}

AnimationRenderer::~AnimationRenderer()
{
}

void AnimationRenderer::Update()
{
	if (m_activeAnimation)
	{
		if (!isStop)
		{
			m_frameCount += Time::deltaTime;

			// duration보다 크면
			if (m_frameCount > m_activeAnimation->GetFrameData()[currentFrame].duration)
			{
				if (!End())
				{
					currentFrame++;
					m_frameCount = 0.f;
				}
				else if (End() && isLoop)
				{
					GotoAndPlay(0);
					m_frameCount = 0.f;
				}
			}
		}
	}
}

void AnimationRenderer::Draw(Camera2D* _camera)
{
	
}

void AnimationRenderer::GotoAndPlay(int _val)
{
	if (m_activeAnimation)
	{
		this->currentFrame = _val;
		this->isStop = false;
	}
}

void AnimationRenderer::GotoAndStop(int _val)
{
	if (m_activeAnimation)
	{
		this->currentFrame = _val;
		this->isStop = true;
	}
}

void AnimationRenderer::Play()
{
	if (m_activeAnimation)
		this->isStop = false;
}

void AnimationRenderer::Stop()
{
	if (m_activeAnimation)
		this->isStop = true;
}

bool AnimationRenderer::End()
{
	return (currentFrame >= m_activeAnimation->GetFrameData().size() - 1) && m_frameCount >= m_activeAnimation->GetFrameData()[currentFrame].duration;
}
