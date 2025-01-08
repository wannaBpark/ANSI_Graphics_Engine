#pragma once

#include "core/ansi_core.h"

namespace ansi 
{
	class Scene;

	class Window
	{
	public:
		explicit Window();
		~Window();

		bool Initialize();
		bool Run();
		
		void SetClientSize(float width, float height) { m_clientSize.x = width; m_clientSize.y = height; }
		void SetNextScene(Scene* nextScene) { m_nextScene = nextScene; }

		const glm::vec2& GetClientSize() const { return m_clientSize; }
	
	private:
		bool OnRenderDefaultGui();		// Render Basic GUI components
		bool ApplyWindowSettings();
		bool ApplyChangeScene();

	private:
		bool m_isWindowed;
		bool m_isBorderless;
		glm::vec2 m_clientSize;		// float�� �̸� ������ ���� : ī�޶� �������� ��� ���� ����
		GLFWwindow* m_window;

		Scene* m_currentScene;
		Scene* m_nextScene;
	};

}

