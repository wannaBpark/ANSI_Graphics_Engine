#include "ansi_object.h"

#include "object/component/transform/ansi_transform.h"

namespace ansi
{
	using namespace std;

	Object::Object(const string& name)
		: m_isEnabled(true)
		, m_isDeleted(false)
		, m_name(name)
		, m_children()
		, m_components()
		, m_parent(nullptr)
		, m_transform(AddComponent<Transform>())
	{

	}

	Object::~Object()
	{
		for (auto it = m_children.begin(); it != m_children.end(); ++it) {
			SAFE_DELETE(it->second);
		}
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			SAFE_DELETE(it->second);
		}
	}

	bool Object::OnUpdate()
	{
		// 비어 있음 (오버라이딩 필요)
		return true;
	}

	/* 오브젝트의 기본 업데이트 : 자식 오브젝트 제거, 업데이트, 컴포넌트 업데이트 등*/
	bool Object::OnDefaultUpdate()
	{
		/* 제거된 모든 자식 오브젝트 제거 */
		for (auto it = m_children.begin(); it != m_children.end(); ) {
			if (it->second->GetIsDeleted()) {
				SAFE_DELETE(it->second);
				it = m_children.erase(it);
			} else {
				++it;
			}
		}

		/* 활성화된 모든 컴포넌트의 업데이트 */
		for (const auto& it : m_components) {
			if (it.second->GetIsEnabled()) {
				CHECK_RF(it.second->OnUpdate());
			}
		}
		
		/* 활성화된 모든 자식 오브젝트 업데이트 */
		for (const auto& it : m_children) {
			if (it.second->GetIsEnabled()) {
				/* 자신의 업데이트를 먼저 하고 */
				CHECK_RF(it.second->OnUpdate());
				/* 자식 오브젝트의 업데이트 실행 */
				CHECK_RF(it.second->OnDefaultUpdate());
			}
		}

		/* 활성화된 모든 컴포넌트의 지연 업데이트 */
		for (const auto& it : m_components) {
			if (it.second->GetIsEnabled()) {
				CHECK_RF(it.second->OnLateUpdate());
			}
		}


		return true;
	}
}