/* 'reinterpret_cast': 'unsigned' 에서 더 큰 'unsigned*' 로의 변환 경고 해제 */
#pragma warning(disable: 4312)

#include "test_scene.h"

#include "utility/shader_loader/ansi_shader_loader.h"


namespace ansi
{
	TestScene::TestScene()
		: m_shaderId(0)
		, m_vertexBufferId(0)
		, m_indexBufferId(0)
		, m_vertexArrayId(0)
	{

	}

	TestScene::~TestScene()
	{
		/* 모든 자원 제거 */
		GL_CHECK(glDeleteProgram(m_shaderId));
		GL_CHECK(glDeleteBuffers(1, &m_vertexBufferId));
		GL_CHECK(glDeleteBuffers(1, &m_indexBufferId));
		GL_CHECK(glDeleteVertexArrays(1, &m_vertexArrayId));

	}

	bool TestScene::CreateResources()
	{
		/* === 테스트용 셰이더 === */
		CHECK_RF(ShaderLoader::Load("asset/shader/test.shader", m_shaderId));

		/* === 삼각형 두 개로 이뤄진 사각형 평면 지오메트리 === */
		/* 지오메트리 자원(버텍스 버퍼 + 인덱스 버퍼 + 버텍스 배열 자원) 생성
		   (버텍스 버퍼: 옷장, 버텍스 배열: 오늘 입을 옷)
		*/
		

		/* 버텍스 데이터 */
		glm::vec3 vertices[] = {
			glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), // 왼쪽 하단, 빨간색
			glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), // 오른쪽 하단, 초록색
			glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), // 오른쪽 상단, 파랑색
			glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), // 왼쪽 상단, 노란색
		};

		/* 인덱스 데이터 */
		glm::uvec3 indices[] = {
			glm::uvec3(0, 1, 2),
			glm::uvec3(2, 3, 0),
		};

		/* 버텍스 버퍼 생성 */
		GL_CHECK_RF(glGenBuffers(1, &m_vertexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));	// 컨텍스트에 장착해야 버퍼 내용 수정 가능
		GL_CHECK_RF(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW));

		/* 인덱스 버퍼 생성 */
		GL_CHECK_RF(glGenBuffers(1, &m_indexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId));
		GL_CHECK_RF(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(glm::uvec3), glm::value_ptr(indices[0]), GL_STATIC_DRAW));

		/* 버텍스 배열 생성 */
		GL_CHECK_RF(glGenVertexArrays(1, &m_vertexArrayId));
		GL_CHECK_RF(glBindVertexArray(m_vertexArrayId));

		/* 버텍스 배열에 버텍스 버퍼 데이터 할당 (버텍스 위치) */
		unsigned stride{ 2 * sizeof(glm::vec3) };	// 버텍스 1개의 용량 (위치+색상 = 2 * sizeof(glm::vec3))
		unsigned offset{ 0 };
		GL_CHECK_RF(glEnableVertexAttribArray(0));	// 위치를 0번으로 지정
		GL_CHECK_RF(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset)));
		
		/* 버텍스 배열에 버텍스 버퍼 데이터 할당 (버텍스 색상) */
		offset += sizeof(glm::vec3);
		GL_CHECK_RF(glEnableVertexAttribArray(1));	// 색상을 1번으로 지정
		GL_CHECK_RF(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset)));

		return true;
	}

	bool TestScene::Initialize()
	{
		CHECK_RF(m_rectangle = AddObject(new Object("Rectangle")));

		return true;
	}

	bool TestScene::OnUpdate()
	{
		static bool isGoRight{ false };

		/* 셰이더를 컨텍스트에 장착 */
		GL_CHECK_RF(glUseProgram(m_shaderId));

		// =============================================

		// 월드 행렬 변경
		if (isGoRight) {
			m_rectangle->GetTransform()->AddPositionX(DELTA_TIME);
			m_rectangle->GetTransform()->AddRotation(DELTA_TIME * 90.0f, DELTA_TIME * 90.0f, DELTA_TIME * 90.0f);

			if (m_rectangle->GetTransform()->GetPosition().x >= 1.0f) { isGoRight = false; }
		} else {
			m_rectangle->GetTransform()->AddPositionX(-DELTA_TIME);
			m_rectangle->GetTransform()->AddRotation(DELTA_TIME * 360.0f, DELTA_TIME * 360.0f, DELTA_TIME * 360.0f);

			if (m_rectangle->GetTransform()->GetPosition().x <= -1.0f) { isGoRight = true; }
		}

		// 셰이더 유니폼 설정
		int location = glGetUniformLocation(m_shaderId, "u_worldMatrix");
		GL_CHECK(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_rectangle->GetTransform()->GetWorldMatrix())));

		// =============================================


		/* 버텍스 배열을 컨텍스트에 장착 */
		GL_CHECK_RF(glBindVertexArray(m_vertexArrayId));

		/* 인덱스 배열을 컨텍스트에 장착 */
		GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId));

		/* 그 상태로 렌더링 (버텍스 3개를 짝지어 삼각형으로, 총 6개의 버텍스) */
		GL_CHECK_RF(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		return true;
	}

	bool TestScene::OnRenderGui()
	{
		return true;
	}


}