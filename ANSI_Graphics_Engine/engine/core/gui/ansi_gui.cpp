#include "ansi_gui.h"

#include "core/ansi_core.h"

namespace ansi
{
	Gui::Gui()
		: m_isCreatedContext(false)
		, m_isInitializedGlfw(false)
		, m_isInitializedOpenGL(false)
		, m_isHoveredWindow(false)
		, m_title("A.N.S.I. Graphics")
	{

	}

	Gui::~Gui()
	{
		if (m_isInitializedOpenGL) { ImGui_ImplOpenGL3_Shutdown(); }
		if (m_isInitializedGlfw)   { ImGui_ImplGlfw_Shutdown(); }
		if (m_isCreatedContext)    { ImGui::DestroyContext(); }
	}

	bool Gui::Initialize()
	{
		CHECK_RF(IMGUI_CHECKVERSION());
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		m_isCreatedContext = true;

		CHECK_PRINT_RF(ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true), "[ImGui Error]: GLFW-binding Creation");
		m_isInitializedGlfw = true;

		CHECK_PRINT_RF(ImGui_ImplOpenGL3_Init("#version 330"), "[ImGui Error]: OpenGL-binding Creation");
		m_isInitializedOpenGL = true;

		return true;
	}
	
	bool Gui::OnRenderBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();		// 새로운 프레임 위해 창크기, 프레임 버퍼 크기 설정
		ImGui_ImplGlfw_NewFrame();			// 새로운 프레임 위해 GUI 렌더링을 위한 내부 Shader 준비 
		ImGui::NewFrame();

		bool isShowWindow{ ImGui::Begin(m_title.c_str()) };			// isShowWindow : 창의 접힘 여부 (접혀있을 경우 GUI 구성 필요 없음)
		m_isHoveredWindow = ImGui::IsWindowHovered(ImGuiHoveredFlags_::ImGuiHoveredFlags_AnyWindow);	// 모든 자식 창 포함하여, 마우스 Hover 감지

		return isShowWindow;
	}
	
	void Gui::OnRenderEnd() // GUI 구성 종료
	{
		ImGui::End();
		ImGui::Render();											// 해당 GUI들을 그리는 함수 (프레임 버퍼는 아닌 어딘가에)
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());		// 위의 Render() 함수 결과를 받아 GUI를 OpenGL3 Shader로 실제 프레임버퍼에 그리는 함수
	}
}