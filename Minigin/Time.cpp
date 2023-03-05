#include "Time.h"

namespace dae
{
	float Time::TotalTime()
	{
		return m_TotalTime;
	}

	float Time::ElapsedSeconds()
	{
		return m_ElapsedSec;
	}

	std::chrono::steady_clock::time_point Time::LastTime()
	{
		return m_LastTime;
	}

	void Time::Update()
	{
		const auto now{ std::chrono::high_resolution_clock::now() };
		m_ElapsedSec = std::chrono::duration<float>(now - m_LastTime).count();
		m_TotalTime += m_ElapsedSec;

		m_LastTime = now;
	}
}