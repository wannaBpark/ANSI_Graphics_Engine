#include "ansi_window.h"
#include "core/timer/ansi_timer.h"
#include "core/gui/ansi_gui.h"
#include "scene/ansi_scene.h"

namespace ansi 
{
	Window::Window()
		: m_isWindowed(false)
		, m_isBorderless(false)
		, m_clientSize(1280.0f, 720.0f)
		, m_window(nullptr)
		, m_currentScene(nullptr)
		, m_nextScene(nullptr)
	{

	}

	Window::~Window()
	{
		SAFE_DELETE(m_currentScene);
		SAFE_DELETE(m_nextScene);		// nxtScene ������ �� �Ǵ� ��� ��ü ���� ����� �� �ֱ� ������ ���� �ʿ�
		glfwTerminate();
	}

	bool Window::Initialize()
	{
		CHECK_PRINT_RF(glfwInit() == GLFW_TRUE, "[GLFW Error]: GLFW Initialization"); // Print if there's initialization error
		PRINT("GLFW Version: " + std::string(glfwGetVersionString()));				  // Print Version

		CHECK_PRINT_RF(m_window = glfwCreateWindow(
			static_cast<int>(m_clientSize.x),
			static_cast<int>(m_clientSize.y),
			"A.N.S.I. Graphics Engine", nullptr, nullptr), "[GLFW Error]: Window Creation");
		GLFW_CHECK(glfwMakeContextCurrent(m_window));
		GLFW_CHECK(glfwSwapInterval(1));

		size_t result{ glewInit() };
		CHECK_PRINT_RF(result == GLEW_OK, glewGetErrorString(result));
		PRINT("GLEW Version: " + std::string(reinterpret_cast<const char*>(glewGetString(GLEW_VERSION))));
		PRINT("OpenGL Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
		PRINT("");

		/* ���� ��� ���� �� ����*/
		m_nextScene = new Scene_A();
		CHECK_RF(ApplyChangeScene());

		return true;
	}

	bool Window::Run()
	{
		while (!glfwWindowShouldClose(m_window)) {
			/* ============================== */
			/*             UPDATE             */
			/* ============================== */

			Core::GetTimer()->OnUpdate();

			/* ============================== */
			/*             RENDER             */
			/* ============================== */

			glClear(GL_COLOR_BUFFER_BIT);

			/* ��� ������ */
			CHECK_RF(m_currentScene->OnUpdate());

			/* GUI Rendering */
			if (Core::GetGui()->OnRenderBegin()) {	// â�� �����ִٸ�(��ȯ��=false) GUI ���� �ʿ� X
				CHECK_RF(m_currentScene->OnRenderGui());	// ��鿡�� ����ϴ� GUI �ٷ� �Ʒ� �⺻ GUI ��ġ
				CHECK_RF(OnRenderDefaultGui());
			}
			Core::GetGui()->OnRenderEnd();			// End(): Begin()�� ��� �Լ�

			/* ============================== */
			/*            HANDLING            */
			/* ============================== */

			GLFW_CHECK(glfwSwapBuffers(m_window));
			GLFW_CHECK(glfwPollEvents());

			/* ������ ���� ����� ���� ���, ��� ���� */
			if (m_nextScene) { 
				CHECK_RF(ApplyChangeScene()); 
			}
		}

		return true;
	}

	bool Window::OnRenderDefaultGui()
	{
		ImGui::Text(">--------- Window Settings ---------<");

		/* [üũ�ڽ�] - â ��� */
		ImGui::Checkbox("Windowed", &m_isWindowed);

		if (m_isWindowed) {
			/* [üũ�ڽ�] - �׵θ� ���� â ��� */
			ImGui::Checkbox("Borderless", &m_isBorderless);

			if (!m_isBorderless) {
				/* [�Է�] - �ػ� */
				ImGui::InputFloat2("Resolution", glm::value_ptr(m_clientSize), "%.0f");
			}
		}

		/* [��ư] - ���� */
		if (ImGui::Button("Apply")) {
			CHECK_RF(ApplyWindowSettings());
		}

		return true;
	}

	bool Window::ApplyWindowSettings()
	{
		/* �� ����� ���� �ҷ����� */
		GLFWmonitor* monitor{ glfwGetPrimaryMonitor() };
		CHECK_PRINT_RF(monitor, "[Window Error]: Can't find primary monitor");

		/* �� ������� ���� ���(�ػ�, ä��, �ֻ���) �ҷ����� */
		const GLFWvidmode* mode{ glfwGetVideoMode(monitor) };
		CHECK_PRINT_RF(mode, "[Window Error]: Can't find video mode");

		if (m_isWindowed) {								// â ��� -> �ػ� ���� ����
			if (m_isBorderless) {
				/* ��ü �ػ󵵷� ȭ�鿡 �� �°� ���� */
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, 0, 0,				// �ι�° �Ű�����(����� ������)�� nullptr�� ��, â ���� �ν���
					mode->width, mode->height, mode->refreshRate));
			} else {
				/* ���� â ��ġ �������� */
				glm::ivec2 windowPosition(0);
				GLFW_CHECK(glfwGetWindowPos(m_window, &windowPosition.x, &windowPosition.y));

				/* GUI�� ������ �ػ󵵷� ���� (������ ������ ���� �����ϱ� ���� ����� ���� ������κ��� �ּ� 50 �ȼ��� ������ �� */
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, glm::max(windowPosition.x, 50), glm::max(windowPosition.y, 50),
					static_cast<int>(m_clientSize.x), static_cast<int>(m_clientSize.y), mode->refreshRate));
			} 
		} else {
			/* â��� X -> ��ü ȭ������ ���� */
			GLFW_CHECK(glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate));
		}

		return true;
	}

	bool Window::ApplyChangeScene()
	{
		SAFE_DELETE(m_currentScene);

		m_currentScene = m_nextScene;
		m_nextScene = nullptr;

		CHECK_RF(m_currentScene->CreateResources());
		CHECK_RF(m_currentScene->Initialize());

		return true;
	}


}