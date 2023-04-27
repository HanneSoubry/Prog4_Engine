#pragma once

#include "Singleton.h"
#include <chrono>

namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		float TotalTime();	// time since start of program
		float ElapsedSeconds(); // seconds since last frame
		std::chrono::steady_clock::time_point LastTime();

		void Update();

	private:
		std::chrono::steady_clock::time_point m_LastTime{ std::chrono::high_resolution_clock::now() };

		float m_ElapsedSec{ 0.f };
		float m_TotalTime{ 0.f };
	};
}