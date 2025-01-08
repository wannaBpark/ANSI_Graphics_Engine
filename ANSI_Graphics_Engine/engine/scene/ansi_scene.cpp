#include "ansi_scene.h"
#include "core/window/ansi_window.h"

namespace ansi
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}

	bool Scene::CreateResources()
	{
		return true;
	}

	bool Scene::Initialize()
	{
		return true;
	}

	bool Scene::OnUpdate()
	{
		return true;
	}

	bool Scene::OnRenderGui()
	{
		return true;
	}

	bool Scene_A::Initialize()
	{
		PRINT("Current Scene is now A");
		return true;
	}

	bool Scene_A::OnUpdate()
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(-1.0f, -0.5f);
		glVertex2f(-0.5f,  0.5f);
		glVertex2f( 0.0f, -0.5f);
		glEnd();

		return true;
	}

	bool Scene_A::OnRenderGui()
	{
		if (ImGui::Button("Change to B")) {
			Core::GetWindow()->SetNextScene(new Scene_B());
		}
		return true;
	}

	bool Scene_B::Initialize()
	{
		PRINT("Current Scene is now B");
		return true;
	}
	
	bool Scene_B::OnUpdate()
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(1.0f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.0f, -0.5f);
		glEnd();

		return true;
	}

	bool Scene_B::OnRenderGui()
	{
		if (ImGui::Button("Change To A")) {
			Core::GetWindow()->SetNextScene(new Scene_A());
		}
		return true;
	}
}