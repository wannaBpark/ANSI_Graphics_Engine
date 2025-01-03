#pragma once

#include "common/ansi_common.h"

namespace ansi 
{
	class Timer;						// 클래스 전방 선언

	class Core 
	{
	public:
		static bool CreateInstance();	// 생성용 정적 함수
		static void DeleteInstance();	// 제거용 정적 함수

		static Core*  GetInstance() { return m_Instance; }			// 접근용 정적 함수
		static Timer* GetTimer()    { return m_Instance->m_timer; }
		
	private:
		explicit Core();	// 생성자
		~Core();			// 소멸자

	private:
		static Core* m_Instance;	// 단일 인스턴스 포인터

		Timer* m_timer;
	};
}

