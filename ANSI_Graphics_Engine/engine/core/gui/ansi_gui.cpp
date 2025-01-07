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
		ImGui_ImplOpenGL3_NewFrame();		// ���ο� ������ ���� âũ��, ������ ���� ũ�� ����
		ImGui_ImplGlfw_NewFrame();			// ���ο� ������ ���� GUI �������� ���� ���� Shader �غ� 
		ImGui::NewFrame();

		bool isShowWindow{ ImGui::Begin(m_title.c_str()) };			// isShowWindow : â�� ���� ���� (�������� ��� GUI ���� �ʿ� ����)
		m_isHoveredWindow = ImGui::IsWindowHovered(ImGuiHoveredFlags_::ImGuiHoveredFlags_AnyWindow);	// ��� �ڽ� â �����Ͽ�, ���콺 Hover ����

		return isShowWindow;
	}
	
	void Gui::OnRenderEnd() // GUI ���� ����
	{
		ImGui::End();
		ImGui::Render();											// �ش� GUI���� �׸��� �Լ� (������ ���۴� �ƴ� ��򰡿�)
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());		// ���� Render() �Լ� ����� �޾� GUI�� OpenGL3 Shader�� ���� �����ӹ��ۿ� �׸��� �Լ�
	}
}