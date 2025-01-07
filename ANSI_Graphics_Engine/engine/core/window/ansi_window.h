#pragma once

#include "core/ansi_core.h"

namespace ansi 
{
	class Window
	{
	public:
		explicit Window();
		~Window();

		bool Initialize();
		bool Run();
		
		void SetClientSize(float width, float height) { m_clientSize.x = width; m_clientSize.y = height; }

		const glm::vec2& GetClientSize() const { return m_clientSize; }

	private:
		glm::vec2 m_clientSize;		// float�� �̸� ������ ���� : ī�޶� �������� ��� ���� ����
		GLFWwindow* m_window;
	};

}

