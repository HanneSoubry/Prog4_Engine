#pragma once

#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		float TotalTime();	// time since start of program
		float ElapsedSeconds(); // seconds since last frame

		void Update();

	private:
		std::chrono::steady_clock::time_point m_LastTime{ std::chrono::high_resolution_clock::now() };

		float m_ElapsedSec{ 0.f };
		float m_TotalTime{ 0.f };
	};
}