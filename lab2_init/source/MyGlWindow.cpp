#define GLM_ENABLE_EXPERIMENTAL 
#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera settings
static float DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

MyGlWindow::MyGlWindow(int w, int h)
{
	m_width = w;
	m_height = h;

	// Initialize viewer with default camera settings
	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);
	float aspect = (w / (float)h);
	
	m_viewer = std::make_unique<Viewer>(viewPoint, viewCenter, upVector, 45.0f, aspect);

	initialize();
}

MyGlWindow::~MyGlWindow()
{
	// Smart pointers will automatically clean up
}

void MyGlWindow::initialize()
{
	// Create shader program using Program class
	try {
		shaderProgram = Program::GenerateFromFileVsFs("shaders/simple.vert", "shaders/simple.frag");
	}
	catch (const std::runtime_error& e) {
		std::cerr << "SHADER ERROR: " << e.what() << std::endl;
		std::cerr << "Failed to load shaders. Please check your shader files." << std::endl;
		exit(1);
	}
	catch (const std::exception& e) {
		std::cerr << "UNEXPECTED ERROR: " << e.what() << std::endl;
		exit(1);
	}

	// Create cube object
	m_cube = std::make_unique<ColorCube>();

	// Enable depth testing for 3D rendering
	glEnable(GL_DEPTH_TEST);
}

void MyGlWindow::draw(void)
{
	// Clear color and depth buffers
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set viewport
	glViewport(0, 0, m_width, m_height);

	// Create transformation matrices
	
	// 1. Model matrix - transform from local to world space
	glm::mat4 model = glm::mat4(1.0f);
	// You can add transformations here, e.g.:
	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// model = glm::scale(model, glm::vec3(0.5f));

	// 2. View matrix - transform from world to camera space
	glm::vec3 eye = m_viewer->getViewPoint();
	glm::vec3 look = m_viewer->getViewCenter();
	glm::vec3 up = m_viewer->getUpVector();
	glm::mat4 view = glm::lookAt(eye, look, up);

	// 3. Projection matrix - transform from camera to clip space
	glm::mat4 projection = glm::perspective(
		glm::radians(m_viewer->getFieldOfView()),
		m_viewer->getAspectRatio(),
		0.1f,
		500.0f
	);

	// Bind shader program and set uniforms
	shaderProgram->BindProgram();
	shaderProgram->SetMatrix("model", model);
	shaderProgram->SetMatrix("view", view);
	shaderProgram->SetMatrix("projection", projection);

	// Draw the cube
	if (m_cube) {
		m_cube->draw();
	}

	// Unbind shader program
	shaderProgram->UnbindProgram();
}
