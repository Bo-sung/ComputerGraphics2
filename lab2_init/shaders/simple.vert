#version 450 
// cpu로 부터 받은 속성 0번의 입력을 vec4로 받음
layout(location = 0) in vec4 vertexPosition;
// cpu로 부터 받은 속성 1벉의 입력을 vec3로 받음
layout(location = 1) in vec3 vertexColor;

out vec3 fcolor;	//fragmentShader로 보낼 정보
void main()
{
	// gl_Position은 빌트인 키워드로서 클립 좌표계를 받아 들인다.
	// 나중에 자동으로 gl_Position값을 perspective division을 해줌

	// 그런데 왜 좌표계 변환을 안하지? 이유는 지금 받은 vertexPosition이 클립 좌표계라고 가정.
	//했기 때문. 그렇기 때문에 곧바로 넣을 수 있음.

	// 중요! : vertex shader에는 반드시 gl_Position 값을 설정해야함.
	gl_Position = vertexPosition;
	fcolor = vertexColor;
}
