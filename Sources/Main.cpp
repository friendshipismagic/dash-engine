/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

// Standard headers
#include <iostream>

// GL Related includes
#include <GL/glew.h>

// Window Manager
#include <GL/freeglut.h>

// GLSL-Like lib
#include <glm/glm.hpp>

// HID Manager lib
#include "HID.h"

// Managers
HID::Manager gHIDManager;

// Reshape callback.
// Called when a reshape of the window is happening
void reshape(int width, int height) {
}

// Display callback.
// called when possible to update the display
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5,-0.5,0.0);
	glVertex3f(0.5,0.0,0.0);
	glVertex3f(0.0,0.5,0.0);
	glEnd();

	glutSwapBuffers();
}

// Motion callback.
// Called when a mouse drag happens
void motion(int x, int y) {
}

// Idle callback.
// Called when nothing else is called
void idle() {
}

// OpenGL context creation
void gl_init_context() {
	// Enable experimental drivers
	glewExperimental = GL_TRUE;

	// Init GLEW
	GLenum err = glewInit();
	if(err != GLEW_OK) {
		// Oops, GLEW failed to start
		std::cerr << "GLEW Fatal error: "
			<< glewGetErrorString(err) << std::endl;
	}

	// Back face culling
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Less depth test for z-buffer
	glEnable(GL_DEPTH_TEST);

	// Force normalization
	glEnable(GL_NORMALIZE);

	// Set the basic line width to be 2px
	glLineWidth(2.0f);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Here we begin.
// Start the FreeGLUT window manager
int main(int argc, char **argv) {

	// Init log system
	// Init config manager
	// Init HID manager
	gHIDManager.init();

	// Init GLUT and create window
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("IGR202");

	// Init OpenGL context
	gl_init_context();

	// Register callbacks
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(HID_manager::keyPressedCallback);
	glutMouseFunc(HID_manager::mouseEventCallback);
	glutSpecialFunc(HID_manager::keyPressedCallback);
	glutMotionFunc(motion);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
