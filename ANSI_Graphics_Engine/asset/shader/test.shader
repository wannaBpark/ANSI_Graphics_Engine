# shader_vertex			// 여기서부터 버텍스 셰이더
# version 460 core			// OpenGL 4.6 버전 사용 명시

layout(location = 0) in vec3 position;	// [입력] - 버텍스 위치 (float 3개)
layout(location = 1) in vec3 color;		// [입력] - 버텍스 색상 (float 3개)

out vec3 v_color;

uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_worldMatrix * vec4(position, 1.0);	// 월드 행렬을 곱해 월드 공간으로 변환
	v_color = color;									// 버텍스 색상을 그대로 넘김
}

# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;	// [출력] - 픽셀의 RGBA (float 4개)

in vec3 v_color;							// [입력] - 버텍스 색상

void main()
{
	FragColor = vec4(v_color, 1.0);			// 버텍스 색상 출력
}