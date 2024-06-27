#pragma once

class Time
{
private:

	static LARGE_INTEGER m_preTime;
	static LARGE_INTEGER m_curTime;
	static LARGE_INTEGER m_frequency;
	static int			 m_frameCount;
	static float		 m_frameTime;
	static float		 m_elapsedTime;
	static int			 m_fps;
	static bool		     m_freezeTime;

public:

	static float     deltaTime;
	static float     timeScale;

	static void		 Initialize();
	static void		 Update();

	static int		 GetFps() { return m_fps; }
	static float	 GetElapsedTime() { return m_elapsedTime; }
	static void		 SetFreezeTime(bool _val) { m_freezeTime = _val; }
	static bool		 GetFreezeTime() { return m_freezeTime; }

};