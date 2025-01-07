#include "ansi_window.h"

#include "core/timer/ansi_timer.h"

namespace ansi 
{
	Window::Window()
		: m_clientSize(1280.0f, 720.0f)
		, m_window(nullptr)
	{

	}

	Window::~Window()
	{
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
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);

		size_t result{ glewInit() };
		CHECK_PRINT_RF(result == GLEW_OK, glewGetErrorString(result));
		PRINT("GLEW Version: " + std::string(reinterpret_cast<const char*>(glewGetString(GLEW_VERSION))));
		PRINT("OpenGL Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
		PRINT("");

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

			glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f( 0.0f,  0.5f);
			glVertex2f( 0.5f, -0.5f);
			glEnd();

			/* ============================== */
			/*            HANDLING            */
			/* ============================== */

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}

		return true;
	}


}