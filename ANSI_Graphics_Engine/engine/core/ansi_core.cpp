#include "ansi_core.h"
#include "timer/ansi_timer.h"
#include "core/window/ansi_window.h"

namespace ansi
{
	Core* Core::m_Instance{ nullptr };
	
	bool Core::CreateInstance()
	{
		if (!m_Instance) {
			m_Instance = new Core();
			m_Instance->Initialize();

			return true;
		} else {
			PRINT_FL("[Core Error]: Duplicated Call");
			
			return false;
		}
	}

	void Core::DeleteInstance()
	{
		SAFE_DELETE(m_Instance);
	}

	Core::Core()
		: m_timer (new Timer())
		, m_window(new Window())
	{

	}
	Core::~Core()
	{
		SAFE_DELETE(m_timer);
		SAFE_DELETE(m_window);
	}
	bool Core::Initialize()
	{
		CHECK_RF(m_window->Initialize());		// If window Init fails -> then Core Init fails

		return true;
	}

}

