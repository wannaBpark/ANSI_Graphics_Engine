#pragma once
#pragma once

/* { 01 } */
/* GLEW */
#include <gl/glew.h>    // GLEW - 기본

/* GLFW */
#include <glfw/glfw3.h> // GLFW - 기본

/* GLM */
#include <glm/glm.hpp>                  // GLM - 기본
#include <glm/gtc/type_ptr.hpp>         // GLM - 타입 생성
#include <glm/gtc/quaternion.hpp>       // GLM - 쿼터니언
#include <glm/gtc/matrix_transform.hpp> // GLM - 행렬 변환

/* ImGui */
#include <imgui.h>              // ImGui - 기본
#include <imgui_impl_glfw.h>    // ImGui - GLFW 관련
#include <imgui_impl_opengl3.h> // ImGui - OpenGL3 관련

/* C++ */
#include <iostream>      // Input/Output Stream - 기본 입출력
#include <fstream>       // File Stream         - 셰이더 로딩
#include <sstream>       // String Stream       - 셰이더 파싱
#include <string>        // String              - 문자열 조작
#include <chrono>        // Chrono              - 시간 측정
#include <typeindex>     // Type Index          - 객체 타입 분별
#include <algorithm>     // Algorithm           - 알고리즘
#include <functional>    // Functional          - 함수 객체
#include <random>        // Random              - 난수 생성
#include <vector>        // Vector              - 동적 배열
#include <unordered_map> // Unordered Map       - 해시 테이블

/* { 02 } */
/* 제거 - 단일 객체 제거 */
#define SAFE_DELETE(ptr) if (ptr) { delete (ptr); (ptr) = nullptr; }
/* 제거 - 배열 객체 제거 */
#define SAFE_DELETE_ARRAY(ptrs) if (ptrs) { delete[] (ptrs); (ptrs) = nullptr; }

/* 콘솔 - 문자열 출력 */
#define PRINT(str) std::cout << (str) << std::endl;
/* 콘솔 - 문자열 + 파일 이름 + 줄 번호 출력 */
#define PRINT_FL(str) std::cout << (str) << ", (FILE: " << (__FILE__) << "), (LINE: " << (__LINE__) << ")" << std::endl;

/* 체크 - 표현식이 false일 경우 false 반환 */
#define CHECK_RF(exp) if (!(exp)) { return false; }
/* 체크 - 표현식이 false일 경우 nullptr 반환 */
#define CHECK_RN(exp) if (!(exp)) { return nullptr; }
/* 체크 - 표현식이 false일 경우 콘솔 창에 문자열 출력 */
#define CHECK_PRINT(exp, str) if (!(exp)) { PRINT(str); }
/* 체크 - 표현식이 false일 경우 콘솔 창에 문자열 출력 후 false 반환 */
#define CHECK_PRINT_RF(exp, str) if (!(exp)) { PRINT(str); return false; }
/* 체크 - 표현식이 false일 경우 콘솔 창에 문자열 출력 후 nullptr 반환 */
#define CHECK_PRINT_RN(exp, str) if (!(exp)) { PRINT(str); return nullptr; }