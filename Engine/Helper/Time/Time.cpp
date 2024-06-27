#include "pch.h"
#include "Time.h"

LARGE_INTEGER Time::m_preTime = { 0,0 };
LARGE_INTEGER Time::m_curTime = { 0,0 };
LARGE_INTEGER Time::m_frequency = { 0,0 };
int			  Time::m_frameCount = 0;
float		  Time::m_frameTime = 0.f;
float		  Time::m_elapsedTime = 0.f;
int			  Time::m_fps = 0;
bool		  Time::m_freezeTime = false;

float		  Time::deltaTime = 0.f;
float		  Time::timeScale = 1.f;

void Time::Initialize()
{
	QueryPerformanceCounter(&m_preTime); // CPU Å¬·°
	QueryPerformanceFrequency(&m_frequency);
}
void Time::Update()
{
	QueryPerformanceCounter(&m_curTime);
	if (!m_freezeTime)
	{
		deltaTime =
			(float)(m_curTime.QuadPart - m_preTime.QuadPart)
			/ (float)(m_frequency.QuadPart)
			* timeScale;

		m_preTime = m_curTime;
		m_frameTime += deltaTime;
		m_elapsedTime += deltaTime;
		m_frameCount++;
	}
	else
	{
		deltaTime = 0.f;
	}


	if (m_frameTime >= 1.f)
	{
		m_fps = (int)(m_frameCount / m_frameTime);
		m_frameTime = 0.f;
		m_frameCount = 0;
	}
}