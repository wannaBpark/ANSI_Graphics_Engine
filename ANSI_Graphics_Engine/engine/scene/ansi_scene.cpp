#include "ansi_scene.h"
#include "core/window/ansi_window.h"

#include "object/ansi_object.h"

namespace ansi
{
	Scene::Scene()
		: m_objects()
	{

	}

	Scene::~Scene()
	{
		for (auto it = m_objects.begin(); it != m_objects.end(); ++it) { SAFE_DELETE(it->second); }
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

	bool Scene::OnDefaultUpdate()
	{
		/* ���ŵ� ��� ������Ʈ ���� */
		for (auto it = m_objects.begin(); it != m_objects.end(); ) {
			if (it->second->GetIsDeleted()) {
				CHECK_RF(it->second);
				m_objects.erase(it);
			}
			else { ++it; }
		}

		/* Ȱ��ȭ�� ��� ������Ʈ ������Ʈ */
		for (const auto& it : m_objects) {
			/* �ڽ��� ������Ʈ�� ���� �ϰ� */
			CHECK_RF(it.second->OnUpdate());
			/* ������Ʈ�� ������Ʈ ���� */
			CHECK_RF(it.second->OnDefaultUpdate());
		}
		
		return true;
	}

}