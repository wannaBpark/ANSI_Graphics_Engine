#pragma once

#include "common/ansi_common.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace ansi
{
	/* 3차원 벡터 전용 상태 검사 클래스 */
	class StateCheckerVec3 : public StateChecker<glm::vec3>
	{
	public:
		/* 생성자
		* @param scalar - 초기화 값 
		*/
		explicit StateCheckerVec3(float scalar = 0.0f) { m_curValue = m_oldValue = glm::vec3(scalar); }

		/* Setter - 현재 값 */
		void Set(const glm::vec3& vec3)		{ m_curValue = vec3; }
		void Set(float x, float y, float z) { m_curValue.x = x; m_curValue.y = y; m_curValue.z = z; }

		/* Setter - 현재 값의 X, Y, Z 요소 */
		void SetX(float x) { m_curValue.x = x; }
		void SetY(float y) { m_curValue.y = y; }
		void SetZ(float z) { m_curValue.z = z; }

		/* Adder - 현재 값 */
		void Add(const glm::vec3& vec3) { m_curValue += vec3; }
		void Add(float x, float y, float z) { m_curValue.x += x, m_curValue.y += y, m_curValue.z += z; }
		
		/* Adder - 현재 값의 X, Y, Z 요소 */
		void AddX(float x) { m_curValue.x += x; }
		void AddY(float y) { m_curValue.y += y; }
		void AddZ(float z) { m_curValue.z += z; }
	};
}