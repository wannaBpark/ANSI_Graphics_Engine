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
		SAFE_DELETE(m_nextScene);		// nxtScene 설정된 후 또는 장면 교체 직전 종료될 수 있기 때문에 제거 필요
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

		/* 시작 장면 설정 및 적용*/
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

			/* 장면 렌더링 */
			CHECK_RF(m_currentScene->OnUpdate());

			/* GUI Rendering */
			if (Core::GetGui()->OnRenderBegin()) {	// 창이 접혀있다면(반환값=false) GUI 렌더 필요 X
				CHECK_RF(m_currentScene->OnRenderGui());	// 장면에서 사용하는 GUI 바로 아래 기본 GUI 배치
				CHECK_RF(OnRenderDefaultGui());
			}
			Core::GetGui()->OnRenderEnd();			// End(): Begin()과 페어 함수

			/* ============================== */
			/*            HANDLING            */
			/* ============================== */

			GLFW_CHECK(glfwSwapBuffers(m_window));
			GLFW_CHECK(glfwPollEvents());

			/* 예약한 다음 장면이 있을 경우, 장면 변경 */
			if (m_nextScene) { 
				CHECK_RF(ApplyChangeScene()); 
			}
		}

		return true;
	}

	bool Window::OnRenderDefaultGui()
	{
		ImGui::Text(">--------- Window Settings ---------<");

		/* [체크박스] - 창 모드 */
		ImGui::Checkbox("Windowed", &m_isWindowed);

		if (m_isWindowed) {
			/* [체크박스] - 테두리 없는 창 모드 */
			ImGui::Checkbox("Borderless", &m_isBorderless);

			if (!m_isBorderless) {
				/* [입력] - 해상도 */
				ImGui::InputFloat2("Resolution", glm::value_ptr(m_clientSize), "%.0f");
			}
		}

		/* [버튼] - 적용 */
		if (ImGui::Button("Apply")) {
			CHECK_RF(ApplyWindowSettings());
		}

		return true;
	}

	bool Window::ApplyWindowSettings()
	{
		/* 주 모니터 정보 불러오기 */
		GLFWmonitor* monitor{ glfwGetPrimaryMonitor() };
		CHECK_PRINT_RF(monitor, "[Window Error]: Can't find primary monitor");

		/* 주 모니터의 비디오 모드(해상도, 채널, 주사율) 불러오기 */
		const GLFWvidmode* mode{ glfwGetVideoMode(monitor) };
		CHECK_PRINT_RF(mode, "[Window Error]: Can't find video mode");

		if (m_isWindowed) {								// 창 모드 -> 해상도 조절 가능
			if (m_isBorderless) {
				/* 전체 해상도로 화면에 딱 맞게 설정 */
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, 0, 0,				// 두번째 매개변수(모니터 포인터)가 nullptr일 때, 창 모드로 인식함
					mode->width, mode->height, mode->refreshRate));
			} else {
				/* 현재 창 위치 가져오기 */
				glm::ivec2 windowPosition(0);
				GLFW_CHECK(glfwGetWindowPos(m_window, &windowPosition.x, &windowPosition.y));

				/* GUI로 선택한 해상도로 설정 (밖으로 나가는 것을 방지하기 위해 모니터 왼쪽 상단으로부터 최소 50 픽셀의 간격을 둠 */
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, glm::max(windowPosition.x, 50), glm::max(windowPosition.y, 50),
					static_cast<int>(m_clientSize.x), static_cast<int>(m_clientSize.y), mode->refreshRate));
			} 
		} else {
			/* 창모드 X -> 전체 화면으로 설정 */
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