#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

	glm::vec2 positions[3] = {
		glm::vec2(-0.5f, -0.5f),
		glm::vec2(0.f, 0.5f),
		glm::vec2(0.5f, -0.5f),
	}; // 이전에 배치한 삼각형의 위치와 동일
	bool isGoRight[3] = { true, true, true };

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// PRIMITIVE : Triangle
		glBegin(GL_TRIANGLES);
		for (size_t i = 0; i < 3; ++i) {
			if (isGoRight[i]) {
				positions[i].x += 1.0f;

				if (positions[i].x > 1.0f) {
					positions[i].x = 1.0f;
					isGoRight[i] = false;
				}
			} else {
				positions[i].x -= 1.0f;
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

	glfwTerminate();
	return 0;
}