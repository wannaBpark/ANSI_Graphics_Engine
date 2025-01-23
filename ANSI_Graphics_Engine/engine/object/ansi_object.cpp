#include "ansi_object.h"

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
		, m_transform(nullptr)
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

	bool Object::OnDefaultUpdate()
	{
		/* 제거된 모든 자식 오브젝트 제거 */
		for (auto it = m_children.begin(); it != m_children.end()) {
			if (it->second->GetIsDeleted()) {
				SAFE_DELETE(it->second);
				it = m_children.erase(it);
			} else {
				++it;
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
		return true;
	}
}