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
		// ��� ���� (�������̵� �ʿ�)
		return true;
	}

	bool Object::OnDefaultUpdate()
	{
		/* ���ŵ� ��� �ڽ� ������Ʈ ���� */
		for (auto it = m_children.begin(); it != m_children.end()) {
			if (it->second->GetIsDeleted()) {
				SAFE_DELETE(it->second);
				it = m_children.erase(it);
			} else {
				++it;
			}
		}
		
		/* Ȱ��ȭ�� ��� �ڽ� ������Ʈ ������Ʈ */
		for (const auto& it : m_children) {
			if (it.second->GetIsEnabled()) {
				/* �ڽ��� ������Ʈ�� ���� �ϰ� */
				CHECK_RF(it.second->OnUpdate());
				/* �ڽ� ������Ʈ�� ������Ʈ ���� */
				CHECK_RF(it.second->OnDefaultUpdate());
			}
		}
		return true;
	}
}