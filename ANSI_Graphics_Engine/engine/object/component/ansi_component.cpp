#include "ansi_component.h"

#include "object/ansi_object.h"

namespace ansi
{
	Component::Component(Object* object)
		: m_isEnabled(true)
		, m_object(object)
	{

	}

	Component::~Component()
	{

	}

	bool Component::OnUpdate()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	bool Component::OnLateUpdate() // ���� ������Ʈ �Լ� : ������Ʈ�� ��� �ڽİ� ������Ʈ ������Ʈ �Լ� ���� �� ȣ��
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

}