#include "common/ansi_common.h"

#include "core/ansi_core.h"
#include "core/timer/ansi_timer.h"

int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	// glfwSwapInterval(0);				// 수직 동기화 (V-Sync) Deactivate

	// If fails to create singleton Core Instance, Terminate
	if (!ansi::Core::CreateInstance()) {
		glfwTerminate();
		return -1;
	}

	glm::vec2 positions[3] = {
		glm::vec2(-0.5f, -0.5f),
		glm::vec2(0.f, 0.5f),
		glm::vec2(0.5f, -0.5f),
	}; // 이전에 배치한 삼각형의 위치와 동일
	bool isGoRight[3] = { true, true, true };

	float timeSum{ 0.0f };
	size_t frameCount{ 0 };
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		ansi::Core::GetTimer()->OnUpdate();

		timeSum += DELTA_TIME;
		++frameCount;
		if (timeSum > 1.0f) {
			std::cout << "FPS : " << frameCount << std::endl;
			timeSum -= 1.0f;
			frameCount = 0;
		}

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// PRIMITIVE : Triangle
		glBegin(GL_TRIANGLES);
		for (size_t i = 0; i < 3; ++i) {
			if (isGoRight[i]) {
				positions[i].x += 1.0f * DELTA_TIME;

				if (positions[i].x > 1.0f) {
					positions[i].x = 1.0f;
					isGoRight[i] = false;
				}
			} else {
				positions[i].x -= 1.0f * DELTA_TIME;
				if (positions[i].x < -1.0f) {
					positions[i].x = -1.0f;
					isGoRight[i] = true;
				}
			}
			glVertex2f(positions[i].x, positions[i].y);
		}
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	ansi::Core::DeleteInstance();

	glfwTerminate();
	return 0;
}