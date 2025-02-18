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
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	bool Component::OnLateUpdate() // 지연 업데이트 함수 : 오브젝트의 모든 자식과 컴포넌트 업데이트 함수 끝난 뒤 호출
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

}