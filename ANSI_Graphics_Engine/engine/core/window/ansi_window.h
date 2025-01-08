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
		glm::vec2 m_clientSize;		// float로 미리 선언한 이유 : 카메라서 행해지는 행렬 연산 위함
		GLFWwindow* m_window;

		Scene* m_currentScene;
		Scene* m_nextScene;
	};

}

