#version 450 
// cpu로 부터 받은 속성 0번의 입력을 vec3로 받음
layout(location = 0) in vec3 vertexPosition;
// cpu로 부터 받은 속성 1번의 입력을 vec3로 받음
layout(location = 1) in vec3 vertexColor;

// Uniform 변수: 변환 행렬
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fcolor;	//fragmentShader로 보낼 정보

void main()
{
	// Model-View-Projection 변환 적용
	gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
	fcolor = vertexColor;
}
