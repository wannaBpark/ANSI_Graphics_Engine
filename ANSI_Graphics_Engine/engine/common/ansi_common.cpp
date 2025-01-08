#include "ansi_common.h"

/* ǥ���İ� �ش� ����, ���� ������ ������ ���� ���ڿ��� �����ϴ� �Լ� */
inline std::string MakeErrorString(const char* errorMessage, const char* filePath, int lineNumber)
{
	return std::string(errorMessage) + " | " + std::string(filePath) + " | " + std::to_string(lineNumber);
}

/* OpenGL �Լ� ���� �� ������ �˻��ϴ� �Լ� */
bool CheckGLError(const char* filePath, int lineNumber)
{
	// glGetError() : ���� ������ OpenGL �Լ��� ���� ��ȣ �� ���� ���� ���ڿ� ����
	GLenum error = glGetError();				
	if (error == GL_NO_ERROR) { return true; }

	std::string errorString{ "[OpenGL Error] (" + std::to_string(error) + ")"  };
	PRINT(MakeErrorString(errorString.c_str(), filePath, lineNumber));

	return false;
}

/* GLFW �Լ� ���� �� ������ �˻��ϴ� �Լ� */
bool CheckGLFWError(const char* filePath, int lineNumber)
{
	const char* errorMessage{ nullptr };
	int error = glfwGetError(&errorMessage);
	if (error == GLFW_NO_ERROR) { return true; }
	
	std::string errorString{ "[GLFW Error] (" + std::to_string(error) + ", " + errorMessage + ")"};
	PRINT(MakeErrorString(errorString.c_str(), filePath, lineNumber));

	return false;
}

