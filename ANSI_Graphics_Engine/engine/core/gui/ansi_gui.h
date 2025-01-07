#pragma once

#include "core/ansi_core.h"

namespace ansi
{
	class Gui
	{
	public:
		explicit Gui();
		~Gui();

		bool Initialize();
		bool OnRenderBegin();
		void OnRenderEnd();

		void SetTitle(const std::string& title) { m_title = title; }

		bool GetIsHoveredWindow() const { return m_isHoveredWindow; }

	private:
		bool m_isCreatedContext;
		bool m_isInitializedGlfw;
		bool m_isInitializedOpenGL;
		bool m_isHoveredWindow;
		std::string m_title;
	};
}

