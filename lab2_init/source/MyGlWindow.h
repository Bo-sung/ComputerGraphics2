//#define  FREEGLUT_LIB_PRAGMAS  0

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include <memory>
#include "Program.h"
#include "ColorCube.h"
#include "Viewer.h"


class MyGlWindow {
public:
	MyGlWindow(int w, int h);
	~MyGlWindow();
	void draw();
	void setSize(int w, int h) { m_width = w; m_height = h; }
	void setAspect(float r) { m_viewer->setAspectRatio(r); }
	
	// Getters for viewer (for mouse control)
	Viewer* getViewer() { return m_viewer.get(); }

private:
	int m_width;
	int m_height;

	std::unique_ptr<Program> shaderProgram;
	std::unique_ptr<ColorCube> m_cube;
	std::unique_ptr<Viewer> m_viewer;

	void initialize();
};
