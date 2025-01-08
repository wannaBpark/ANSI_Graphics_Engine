#include "ansi_common.h"

/* 표현식과 해당 파일, 라인 정보를 조합해 에러 문자열을 생성하는 함수 */
inline std::string MakeErrorString(const char* errorMessage, const char* filePath, int lineNumber)
{
	return std::string(errorMessage) + " | " + std::string(filePath) + " | " + std::to_string(lineNumber);
}

/* OpenGL 함수 실행 후 에러를 검사하는 함수 */
bool CheckGLError(const char* filePath, int lineNumber)
{
	// glGetError() : 직전 실행한 OpenGL 함수의 에러 번호 및 에러 정보 문자열 주입
	GLenum error = glGetError();				
	if (error == GL_NO_ERROR) { return true; }

	std::string errorString{ "[OpenGL Error] (" + std::to_string(error) + ")"  };
	PRINT(MakeErrorString(errorString.c_str(), filePath, lineNumber));

	return false;
}

/* GLFW 함수 실행 후 에러를 검사하는 함수 */
bool CheckGLFWError(const char* filePath, int lineNumber)
{
	const char* errorMessage{ nullptr };
	int error = glfwGetError(&errorMessage);
	if (error == GLFW_NO_ERROR) { return true; }
	
	std::string errorString{ "[GLFW Error] (" + std::to_string(error) + ", " + errorMessage + ")"};
	PRINT(MakeErrorString(errorString.c_str(), filePath, lineNumber));

	return false;
}

