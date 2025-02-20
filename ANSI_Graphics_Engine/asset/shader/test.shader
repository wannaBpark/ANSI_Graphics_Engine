# shader_vertex			// ���⼭���� ���ؽ� ���̴�
# version 460 core			// OpenGL 4.6 ���� ��� ���

layout(location = 0) in vec3 position;	// [�Է�] - ���ؽ� ��ġ (float 3��)
layout(location = 1) in vec3 color;		// [�Է�] - ���ؽ� ���� (float 3��)

out vec3 v_color;

uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_worldMatrix * vec4(position, 1.0);	// ���� ����� ���� ���� �������� ��ȯ
	v_color = color;									// ���ؽ� ������ �״�� �ѱ�
}

# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;	// [���] - �ȼ��� RGBA (float 4��)

in vec3 v_color;							// [�Է�] - ���ؽ� ����

void main()
{
	FragColor = vec4(v_color, 1.0);			// ���ؽ� ���� ���
}