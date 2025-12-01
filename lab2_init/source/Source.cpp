
//#define GLFW_INCLUDE_GLU

#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
//#include <memory>
#include "MyGlWindow.h"

std::unique_ptr<MyGlWindow> win;

// Mouse state
static double lastX = 0, lastY = 0;
static bool leftButtonPressed = false;
static bool middleButtonPressed = false;
static bool rightButtonPressed = false;
static int g_width = 800;
static int g_height = 800;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	double deltaX = xpos - lastX;
	double deltaY = ypos - lastY;

	if (leftButtonPressed)
	{
		// Rotate
		win->getViewer()->rotate(deltaX / (float)g_width, deltaY / (float)g_height);
	}
	else if (middleButtonPressed)
	{
		// Pan
		win->getViewer()->translate(-deltaX / (float)g_width, deltaY / (float)g_height, true);
	}
	else if (rightButtonPressed)
	{
		// Zoom (alternative to scroll)
		win->getViewer()->zoom(deltaY / (float)g_height);
	}

	lastX = xpos;
	lastY = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS) leftButtonPressed = true;
		else if (action == GLFW_RELEASE) leftButtonPressed = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		if (action == GLFW_PRESS) middleButtonPressed = true;
		else if (action == GLFW_RELEASE) middleButtonPressed = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS) rightButtonPressed = true;
		else if (action == GLFW_RELEASE) rightButtonPressed = false;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Zoom with scroll
	win->getViewer()->zoom(-yoffset * 0.1f);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	g_width = width;
	g_height = height;
	win->setSize(width, height);
	win->setAspect(width / (float)height);
}

int main(void)
{

	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(g_width, g_height, "OpenGL FrameWork", NULL,
		NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	// 윈도우 제대로 생성 ->

	// openGL 컨텍스트 생성 -> 컨텍스트? 구조체 생성

	// openGL 구조체 생성
	glfwMakeContextCurrent(window);
	
	// Register callbacks
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

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
	win = std::make_unique<MyGlWindow>(g_width, g_height);

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
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


