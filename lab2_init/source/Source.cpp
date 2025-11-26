
//#define GLFW_INCLUDE_GLU

#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
//#include <memory>
#include "MyGlWindow.h"

std::unique_ptr<MyGlWindow> win;
int main(void)
{

	if (!glfwInit())
	{

	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 800;
	int height = 800;
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL FrameWork", NULL,
		NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	// 윈도우 제대로 생성 ->

	// openGL 컨텍스트 생성 -> 컨텍스트? 구조체 생성

	// openGL 구조체 생성
	glfwMakeContextCurrent(window);
	if (gl3wInit()) {
		fprintf(stderr, "failed to initialize OpenGL\n");
		return -1;
	}
	if (!gl3wIsSupported(3, 2)) {
		fprintf(stderr, "OpenGL 3.2 not supported\n");
		return -1;
	}
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
		glGetString(GL_SHADING_LANGUAGE_VERSION));
	glfwSwapInterval(1);

	// MyGlWindow 객체 생성
	//win = new MyGlWindow(width, height); // c++ 98 방식
	// Modern c++ 이용 : 스마트 포인터(필수로 익혀둘것)
	win = std::make_unique<MyGlWindow>(width, height);

	printf("OpenGL %s, GLSL %s\n",
		glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	while (!glfwWindowShouldClose(window))
	{
		// 여기에 뭔가 그려줘야함.

		// 매 프레임 draw() 함수 호출
		win->draw();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
	}
	glfwPollEvents();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


