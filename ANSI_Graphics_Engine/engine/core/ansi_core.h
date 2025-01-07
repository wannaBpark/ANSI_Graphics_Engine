#pragma once

#include "common/ansi_common.h"

namespace ansi 
{
	class Timer;						// 클래스 전방 선언
	class Window;
	class Gui;

	class Core 
	{
	public:
		static bool CreateInstance();	// 생성용 정적 함수
		static void DeleteInstance();	// 제거용 정적 함수

		static Core*   GetInstance() { return m_Instance; }				// 접근용 정적 함수
		static Timer*  GetTimer()    { return m_Instance->m_timer; }
		static Window* GetWindow()   { return m_Instance->m_window; }
		static Gui* GetGui()		 { return m_Instance->m_gui; }
		
	private:
		explicit Core();	// 생성자
		~Core();			// 소멸자

		bool Initialize();

	private:
		static Core* m_Instance;	// 단일 인스턴스 포인터

		Timer*  m_timer;
		Window* m_window;
		Gui* m_gui;
	};
}

