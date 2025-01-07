#pragma once

#include "common/ansi_common.h"

namespace ansi 
{
	class Timer;						// Ŭ���� ���� ����
	class Window;

	class Core 
	{
	public:
		static bool CreateInstance();	// ������ ���� �Լ�
		static void DeleteInstance();	// ���ſ� ���� �Լ�

		static Core*   GetInstance() { return m_Instance; }				// ���ٿ� ���� �Լ�
		static Timer*  GetTimer()    { return m_Instance->m_timer; }
		static Window* GetWindow()   { return m_Instance->m_window; }
		
	private:
		explicit Core();	// ������
		~Core();			// �Ҹ���

		bool Initialize();

	private:
		static Core* m_Instance;	// ���� �ν��Ͻ� ������

		Timer*  m_timer;
		Window* m_window;
	};
}

