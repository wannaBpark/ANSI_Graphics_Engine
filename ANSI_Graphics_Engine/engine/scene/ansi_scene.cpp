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
		/* 제거된 모든 오브젝트 제거 */
		for (auto it = m_objects.begin(); it != m_objects.end(); ) {
			if (it->second->GetIsDeleted()) {
				CHECK_RF(it->second);
				m_objects.erase(it);
			}
			else { ++it; }
		}

		/* 활성화된 모든 오브젝트 업데이트 */
		for (const auto& it : m_objects) {
			/* 자신의 업데이트를 먼저 하고 */
			CHECK_RF(it.second->OnUpdate());
			/* 오브젝트의 업데이트 실행 */
			CHECK_RF(it.second->OnDefaultUpdate());
		}
		
		return true;
	}

}