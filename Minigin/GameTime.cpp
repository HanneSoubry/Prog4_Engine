#include "GameTime.h"

namespace dae
{
	float GameTime::TotalTime()
	{
		return m_TotalTime;
	}

	float GameTime::ElapsedSeconds()
	{
		return m_ElapsedSec;
	}

	std::chrono::steady_clock::time_point GameTime::LastTime()
	{
		return m_LastTime;
	}

	void GameTime::Update()
	{
		const auto now{ std::chrono::high_resolution_clock::now() };
		m_ElapsedSec = std::chrono::duration<float>(now - m_LastTime).count();
		m_TotalTime += m_ElapsedSec;

		m_LastTime = now;
	}
}