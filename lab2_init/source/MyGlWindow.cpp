
#define GLM_ENABLE_EXPERIMENTAL 
#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

MyGlWindow::MyGlWindow(int w, int h)
{
	m_width = w;
	m_height = h;

	setupBuffer();
}

void MyGlWindow::setupBuffer()
{
	// 쉐이더 객체 생성 : modern c++
	shaderProgram = std::make_unique<ShaderProgram>();

	//load shaders : vertex shader와 fragment shader 지정
	shaderProgram->initFromFiles("shaders/simple.vert", "shaders/simple.frag");

	// Non-DSA(Direct State Area)방법
	// 삼각형 위치 저장 : 0
	const float vertexPosition[] = {
		0.0f, 0.0f , 0.0f, 1.0f,
		0.4f, 0.0f , 0.0f, 1.0f,
		0.0f, 0.4f , 0.0f, 1.0f,
		0.4f, 0.4f , 0.0f, 1.0f,
	};

	// 삼각형 색상 저장 : 1
	const float vertexColor[] = {
		1.0f, 0.0f , 0.0f,
		0.0f, 1.0f , 0.0f,
		0.0f, 0.0f , 1.0f,
		1.0f, 0.0f , 0.0f,
	};

	const float vertices[] = {		// interleave 방식
		-0.5f, 0.0f , 0.0f, 1.0f,				1.0f, 0.0f , 0.0f,
		0.5f, 0.0f , 0.0f, 1.0f,				0.0f, 1.0f , 0.0f,
		0.0f, 0.5f , 0.0f, 1.0f,				0.0f, 0.0f , 1.0f,
	};

	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0,
	};
	GLfloat cube_colors[] = {
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};


	GLushort cube_elements[] = {
	0, 1, 2,	2, 3, 0,	1, 5, 6,
	6, 2, 1,	7, 6, 5,	5, 4, 7,
	4, 0, 3,	3, 7, 4,	4, 5, 1,
	1, 0, 4,	3, 2, 6,	6, 7, 3,
	};

	// 이제 삼각형에 대한 정보를 CPU가 아닌 GPU에 보냄
	// 삼각형이 가진 속성 정보 : 위치, 생성
	// VAO 생성.(Vertex Array Object)
	glGenVertexArrays(1, &vaoHandle);	// 컨테이너 생성
	glBindVertexArray(vaoHandle);		// 바인드 : 여러개의 VAO 중에 어떤거 사용할지
	// 바인드 : activate의 의미. 난 앞으로 여기다 뭔가 작업을 할래
	// VBO 생성 (Vertex Buffer Object) : vertex의 속성 정보 저장
	GLuint vboPosition;
	glGenBuffers(1, &vboPosition); // vertex 위치 정보를 저장하기 위한 vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboPosition); // vbo바인딩 : activate

	// 데이터를 메인 메모리 -> GPU 메모리로 보낸 후 할당 : 마지막 : USAGE
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(		// GPU 한태 메머리에 얼라온 데이터 해것 방법을 알려줌
		0,			// 속성 해석
		3,			// 데이터 수 (vertex 당)
		GL_FLOAT,	// 데이터 타입
		GL_FALSE,	// 정규화 여부
		0,			// STRIDE
		0			// OFFSET
	);
	glEnableVertexAttribArray(0);	// 속성 0번 활성화

	GLuint vboColor;
	glGenBuffers(1, &vboColor); // vertex 색상 정보를 저장하기 위한 vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboColor); // vbo바인딩 : activate

	// 데이터를 메인 메모리 -> GPU 메모리로 보낸 후 할당 : 마지막 : USAGE
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), &cube_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(		// GPU 한태 메머리에 얼라온 데이터 해석 방법을 알려줌
		1,			// 속성 번호
		3,			// 데이터 수 (vertex 당)
		GL_FLOAT,	// 데이터 타입
		GL_FALSE,	// 정규화 여부
		0,			// STRIDE
		0			// OFFSET
	);
	glEnableVertexAttribArray(1);	// 속성 1번 활성화

	GLuint ibo_cube_elements;

	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	//vao unbound
	glBindVertexArray(0);		// 현재 사용중인 vao unbound (0을 넣으면 됨)


	//	
	//	glGenVertexArrays(1, &vaoHandle);	// 컨테이너 생성
	//	glBindVertexArray(vaoHandle);		// 바인드 : 여러개의 VAO 중에 어떤거 사용할지
	//	GLuint vbo_vertex;
	//	glGenBuffers(1, &vbo_vertex); // vertex 위치 정보를 저장하기 위한 vbo
	//	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex); // vbo바인딩 : activate
	//	
	//	// 데이터를 메인 메모리 -> GPU 메모리로 보낸 후 할당 : 마지막 : USAGE
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	//	// 위치 데이터
	//	glVertexAttribPointer(		// GPU 한태 메머리에 얼라온 데이터 해석 방법을 알려줌
	//		0,							// 속성 번호
	//		4,							// 데이터 수 (vertex 당)
	//		GL_FLOAT,					// 데이터 타입
	//		GL_FALSE,					// 정규화 여부
	//		sizeof(float) * 7,			// STRIDE : 위치가 시작한 후에, 얼마 데이터 후에 다시 위치가 시작하나?
	//		(void *) 0					// OFFSET
	//	);
	//	glEnableVertexAttribArray(0);	// 속성 1번 활성화
	//	// 색상 데이터
	//	glVertexAttribPointer(		// GPU 한태 메머리에 얼라온 데이터 해석 방법을 알려줌
	//		1,							// 속성 번호
	//		3,							// 데이터 수 (vertex 당)
	//		GL_FLOAT,					// 데이터 타입
	//		GL_FALSE,					// 정규화 여부
	//		sizeof(float) * 7,			// STRIDE : 위치가 시작한 후에, 얼마 데이터 후에 다시 위치가 시작하나?
	//		(void*) (sizeof(float) * 4)					// OFFSET
	//	);
	//	glEnableVertexAttribArray(1);	// 속성 1번 활성화
	//	
	//	//vao unbound
	//	glBindVertexArray(0);		// 현재 사용중인 vao unbound (0을 넣으면 됨)


	// DSA 방식 : 함수 명이 다름. (glBinding... 이 없음)
	/*
	//1. vao 생성
	GLuint vbo_position;
	GLuint vbo_color;
	// glCreate.... -> DSA 방식
	glCreateVertexArrays(1, &vaoHandle);
	glCreateBuffers(1, &vbo_position);
	glCreateBuffers(1, &vbo_color);

	// Position 처리
	// GPU 메모리 할당
	glNamedBufferData(vbo_position, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(
		vaoHandle,					// vao
		0,							// binding Index번호
		vbo_position,				// vbo
		0,							// Offset
		sizeof(float) * 4			// Stride
	);

	// Color 처리
	// GPU 메모리 할당
	glNamedBufferData(vbo_color, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(
		vaoHandle,					// vao
		1,							// binding Index 번호
		vbo_position,				// vbo
		0,							// Offset
		sizeof(float) * 3			// Stride
	);

	glVertexArrayAttribFormat(vaoHandle,
		0,			// bindingIndex
		4,			// vertex당 데이터 수
		GL_FLOAT,
		GL_FALSE,
		0			//	offset
	);

	glVertexArrayAttribBinding(vaoHandle,
		0,		// 속성번호
		0		// binding index
	);
	glEnableVertexArrayAttrib(vaoHandle, 0);	//0번 속성 enable


	glVertexArrayAttribFormat(vaoHandle,
		1,			// bindingIndex
		3,			// vertex당 데이터 수
		GL_FLOAT,
		GL_FALSE,
		0			//	offset
	);

	glVertexArrayAttribBinding(vaoHandle,
		1,		// 속성번호
		1		// binding index
	);
	glEnableVertexArrayAttrib(vaoHandle, 1);	//0번 속성 enable

	*/

	/*
	//1. vao 생성
	GLuint vbo_vertex;
	// glCreate.... -> DSA 방식
	glCreateVertexArrays(1, &vaoHandle);
	glCreateBuffers(1, &vbo_vertex);

	glNamedBufferData(vbo_vertex, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(
		vaoHandle,					// vao
		0,							// binding Index 번호
		vbo_vertex,					// vbo
		0,							// Offset
		sizeof(float) * 7			// Stride
	);

	glVertexArrayAttribFormat(vaoHandle, 0, 4, GL_FLOAT, GL_FALSE, 0); // 마지막 0 : offset
	glVertexArrayAttribBinding(vaoHandle, 0, 0);	// 0: 속성번호, 0 : binding Index
	glEnableVertexArrayAttrib(vaoHandle, 0);		// 속성번호 0 활성화

	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4); // 마지막 sizeof(float) * 4 : offset
	glVertexArrayAttribBinding(vaoHandle, 1, 0);	// 1: 속성번호, 0 : binding Index
	glEnableVertexArrayAttrib(vaoHandle, 1);		// 속성번호 1 활성화
	*/


}



void MyGlWindow::draw(void)
{
	glClearColor(0, 0, 0, 1);	//백그라운드 색상 지정

	// 어떤 버퍼를 지울지 지정. : 라스터라이제이션 할때 두 개의 버퍼 : COLOR, DEPTH
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 0. 뷰포트 설정 : 캔버스 크기 및 위치 설정 : 현재는 800 X 600인데 이걸 다 쓸건지 일부만 쓸건지 결정
	// 
	// 

	glViewport(0, 0, m_width, m_height); // 앞 2개값 : 시작점. 뒤 두개 : 크기
	//1. 쉐이더 use
	shaderProgram->use();

	//2.vao binding
	glBindVertexArray(vaoHandle);

	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

	shaderProgram->disable();
}
