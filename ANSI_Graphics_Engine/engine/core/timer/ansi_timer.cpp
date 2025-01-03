#include "ansi_timer.h"

namespace ansi
{
	Timer::Timer()
		: m_deltaTime(0.0f)
		, m_currentTime(std::chrono::high_resolution_clock::now())
		, m_previousTime(std::chrono::high_resolution_clock::now())
		, m_elapsedTick(0)
	{

	}

	void Timer::OnUpdate()
	{
		m_currentTime = std::chrono::high_resolution_clock::now();
		m_elapsedTick = m_currentTime - m_previousTime;				// 시간 간격 계산
		m_previousTime = m_currentTime;
		m_deltaTime = m_elapsedTick.count() / 1000000000.0f;		// 초 단위로 변환
	}
}