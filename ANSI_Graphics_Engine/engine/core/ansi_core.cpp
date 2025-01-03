#include "ansi_core.h"

namespace ansi
{
	Core* Core::m_Instance{ nullptr };
	
	bool Core::CreateInstance()
	{
		if (!m_Instance) {
			m_Instance = new Core();

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
	{

	}
	Core::~Core()
	{

	}	
}

