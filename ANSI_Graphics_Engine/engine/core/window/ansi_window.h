#pragma once

#include "core/ansi_core.h"

namespace ansi 
{
	class Scene;
	class EventListener;

	class Window
	{
	public:
		explicit Window();
		~Window();

		bool Initialize();
		bool Run();

		void AddEventListener(EventListener* listener) { m_eventListeners.push_back(listener); }
		void RemoveEventListener(EventListener* listener) { m_eventListeners.erase(std::remove(m_eventListeners.begin(), m_eventListeners.end(), listener), m_eventListeners.end()); }
		
		void SetClientSize(float width, float height) { m_clientSize.x = width; m_clientSize.y = height; }
		void SetMousePosition(float x, float y) { m_mousePosition.x = x, m_mousePosition.y = y; }
		void SetNextScene(Scene* nextScene) { m_nextScene = nextScene; }

		const glm::vec2& GetClientSize() const { return m_clientSize; }
		const glm::vec2& GetMousePosition() const { return m_mousePosition; }
		const std::vector<EventListener* >& GetEventListeners() const { return m_eventListeners; }
	
	private:
		bool OnRenderDefaultGui();		// Render Basic GUI components
		bool ApplyWindowSettings();
		bool ApplyChangeScene();

	private:
		bool m_isWindowed;
		bool m_isBorderless;
		glm::vec2 m_clientSize;		// float로 미리 선언한 이유 : 카메라서 행해지는 행렬 연산 위함
		glm::vec2 m_mousePosition;
		GLFWwindow* m_window;

		Scene* m_currentScene;
		Scene* m_nextScene;

		std::vector<EventListener* > m_eventListeners;
	};

}

