/* 'reinterpret_cast': 'unsigned' ���� �� ū 'unsigned*' ���� ��ȯ ��� ���� */
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
		/* ��� �ڿ� ���� */
		GL_CHECK(glDeleteProgram(m_shaderId));
		GL_CHECK(glDeleteBuffers(1, &m_vertexBufferId));
		GL_CHECK(glDeleteBuffers(1, &m_indexBufferId));
		GL_CHECK(glDeleteVertexArrays(1, &m_vertexArrayId));

	}

	bool TestScene::CreateResources()
	{
		/* === �׽�Ʈ�� ���̴� === */
		CHECK_RF(ShaderLoader::Load("asset/shader/test.shader", m_shaderId));

		/* === �ﰢ�� �� ���� �̷��� �簢�� ��� ������Ʈ�� === */
		/* ������Ʈ�� �ڿ�(���ؽ� ���� + �ε��� ���� + ���ؽ� �迭 �ڿ�) ����
		   (���ؽ� ����: ����, ���ؽ� �迭: ���� ���� ��)
		*/
		

		/* ���ؽ� ������ */
		glm::vec3 vertices[] = {
			glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), // ���� �ϴ�, ������
			glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), // ������ �ϴ�, �ʷϻ�
			glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), // ������ ���, �Ķ���
			glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), // ���� ���, �����
		};

		/* �ε��� ������ */
		glm::uvec3 indices[] = {
			glm::uvec3(0, 1, 2),
			glm::uvec3(2, 3, 0),
		};

		/* ���ؽ� ���� ���� */
		GL_CHECK_RF(glGenBuffers(1, &m_vertexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));	// ���ؽ�Ʈ�� �����ؾ� ���� ���� ���� ����
		GL_CHECK_RF(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW));

		/* �ε��� ���� ���� */
		GL_CHECK_RF(glGenBuffers(1, &m_indexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId));
		GL_CHECK_RF(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(glm::uvec3), glm::value_ptr(indices[0]), GL_STATIC_DRAW));

		/* ���ؽ� �迭 ���� */
		GL_CHECK_RF(glGenVertexArrays(1, &m_vertexArrayId));
		GL_CHECK_RF(glBindVertexArray(m_vertexArrayId));

		/* ���ؽ� �迭�� ���ؽ� ���� ������ �Ҵ� (���ؽ� ��ġ) */
		unsigned stride{ 2 * sizeof(glm::vec3) };	// ���ؽ� 1���� �뷮 (��ġ+���� = 2 * sizeof(glm::vec3))
		unsigned offset{ 0 };
		GL_CHECK_RF(glEnableVertexAttribArray(0));	// ��ġ�� 0������ ����
		GL_CHECK_RF(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset)));
		
		/* ���ؽ� �迭�� ���ؽ� ���� ������ �Ҵ� (���ؽ� ����) */
		offset += sizeof(glm::vec3);
		GL_CHECK_RF(glEnableVertexAttribArray(1));	// ������ 1������ ����
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

		/* ���̴��� ���ؽ�Ʈ�� ���� */
		GL_CHECK_RF(glUseProgram(m_shaderId));

		// =============================================

		// ���� ��� ����
		if (isGoRight) {
			m_rectangle->GetTransform()->AddPositionX(DELTA_TIME);
			m_rectangle->GetTransform()->AddRotation(DELTA_TIME * 90.0f, DELTA_TIME * 90.0f, DELTA_TIME * 90.0f);

			if (m_rectangle->GetTransform()->GetPosition().x >= 1.0f) { isGoRight = false; }
		} else {
			m_rectangle->GetTransform()->AddPositionX(-DELTA_TIME);
			m_rectangle->GetTransform()->AddRotation(DELTA_TIME * 360.0f, DELTA_TIME * 360.0f, DELTA_TIME * 360.0f);

			if (m_rectangle->GetTransform()->GetPosition().x <= -1.0f) { isGoRight = true; }
		}

		// ���̴� ������ ����
		int location = glGetUniformLocation(m_shaderId, "u_worldMatrix");
		GL_CHECK(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_rectangle->GetTransform()->GetWorldMatrix())));

		// =============================================


		/* ���ؽ� �迭�� ���ؽ�Ʈ�� ���� */
		GL_CHECK_RF(glBindVertexArray(m_vertexArrayId));

		/* �ε��� �迭�� ���ؽ�Ʈ�� ���� */
		GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId));

		/* �� ���·� ������ (���ؽ� 3���� ¦���� �ﰢ������, �� 6���� ���ؽ�) */
		GL_CHECK_RF(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		return true;
	}

	bool TestScene::OnRenderGui()
	{
		return true;
	}


}