#pragma once

#include "object/component/ansi_component.h"
#include "utility/state_checker/ansi_state_checker_math.h"

namespace ansi
{
	class Transform : public Component
	{
	public:
		explicit Transform(Object* object);
		bool OnLateUpdate() override;
		void Reset();
		glm::vec3 GetLookAt(const glm::vec3& dir = glm::vec3(0.0f, 0.0f, 1.0f)) const;

#pragma region Setters
		// Setters
		void SetPosition(const glm::vec3& position) { m_position.Set(position); }
		void SetPosition(float x, float y, float z) { m_position.Set(x, y, z); }
		void SetPositionX(float x) { m_position.SetX(x); }
		void SetPositionY(float y) { m_position.SetY(y); }
		void SetPositionZ(float z) { m_position.SetZ(z); }
		void SetEulerOrder(EulerOrder order)		{ m_eulerOrder = order; }
		void SetRotation(const glm::vec3& rotation) { m_rotation.Set(rotation); }
		void SetRotation(float x, float y, float z) { m_rotation.Set(x, y, z); }
		void SetRotationX(float x) { m_rotation.SetX(x); }
		void SetRotationY(float y) { m_rotation.SetY(y); }
		void SetRotationZ(float z) { m_rotation.SetZ(z); }
		void SetScale(const glm::vec3& scale)	{ m_scale.Set(scale); }
		void SetScale(float x, float y, float z){ m_scale.Set(x, y, z); }
		void SetScale(float scale)				{ m_scale.Set(scale, scale, scale); }
		void SetScaleX(float x) { m_scale.SetX(x); }
		void SetScaleY(float y) { m_scale.SetY(y); }
		void SetScaleZ(float z) { m_scale.SetZ(z); }
#pragma endregion
#pragma region Adders
		// Adders
		void AddPosition(const glm::vec3& position) { m_position.Add(position); }
		void AddPosition(float x, float y, float z) { m_position.Add(x, y, z); }
		void AddPositionX(float x) { m_position.AddX(x); }
		void AddPositionY(float y) { m_position.AddY(y); }
		void AddPositionZ(float z) { m_position.AddZ(z); }
		void AddRotation(const glm::vec3& rotation) { m_rotation.Add(rotation); }
		void AddRotation(float x, float y, float z) { m_rotation.Add(x, y, z); }
		void AddRotationX(float x) { m_rotation.AddX(x); }
		void AddRotationY(float y) { m_rotation.AddY(y); }
		void AddRotationZ(float z) { m_rotation.AddZ(z); }
		void AddScale(const glm::vec3& scale) { m_scale.Add(scale); }
		void AddScale(float x, float y, float z) { m_scale.Add(x, y, z); }
		void AddScaleX(float x) { m_scale.AddX(x); }
		void AddScaleY(float y) { m_scale.AddY(y); }
		void AddScaleZ(float z) { m_scale.AddZ(z); }
#pragma endregion
#pragma region Getters
		bool GetIsChangedMatrix()		const { return m_isChangedMatrix; }
		EulerOrder GetEulerOrder()		const { return m_eulerOrder; }
		const glm::vec3& GetPosition()  const { return m_position.Get(); }
		const glm::vec3& GetRotation()  const { return m_rotation.Get(); }
		const glm::vec3& GetScale()		const { return m_scale.Get(); }
		const glm::vec3& GetWorldPosition() const { return m_worldPosition; }
		const glm::mat4& GetWorldMatrix()	const { return m_worldMatrix; }
		const glm::mat4& GetParentMatrix()	const { return m_parentMatrix; }
#pragma endregion
	private:
		bool m_isChangedMatrix;			/* 이번 프레임에 월드 행렬이 변경되었는지 여부 */
		EulerOrder m_eulerOrder;		/* 오일러각 회전 순서 */
		glm::vec3 m_worldPosition;		/* 월드 공간의 최종 위치 */
		glm::mat4 m_localMatrix;		/* 로컬 행렬 */
		glm::mat4 m_worldMatrix;		/* 월드 행렬 */
		glm::mat4 m_parentMatrix;		/* 부모의 월드 행렬 */
		StateCheckerVec3 m_position;	/* 위치 (상태 검사) */
		StateCheckerVec3 m_rotation;	/* 회전 (상태 검사) */
		StateCheckerVec3 m_scale;		/* 크기 (상태 검사) */

	};

}

