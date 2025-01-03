#pragma once

#include "core/ansi_core.h"

#define DELTA_TIME ansi::Core::GetTimer()->GetDeltaTime()

namespace ansi
{
	class Timer
	{
	public:
		explicit Timer();
		
		void OnUpdate();

		float GetDeltaTime() const { return m_deltaTime; }

	private:
		float m_deltaTime;
		std::chrono::steady_clock::time_point m_currentTime;
		std::chrono::steady_clock::time_point m_previousTime;
		std::chrono::nanoseconds m_elapsedTick;
	};
}

