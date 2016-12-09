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
#include <memory>

// GL Related includes
#include <GL/glew.h>

// Window Manager
#include <GL/freeglut.h>

// GLSL-Like lib
#include <glm/glm.hpp>

// HID Manager lib
#include "HID.h"

// Config Manager lib
#include "Ressources/Ressources.h"
#include "Ressources/Config.h"

// Managers
std::shared_ptr<Ressources::Manager> gRessourcesManager;
std::shared_ptr<Ressources::Config> gConfigManager;
std::shared_ptr<HID::Manager> gHIDManager;

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

// This function should just call the HID manager
void keyPressedCallback(unsigned char key, int x, int y) {
	gHIDManager->keyPressedCallback(key, x, y);
}

// This function should just call the HID manager
void specialKeyPressedCallback(int key, int x, int y) {
	gHIDManager->specialKeyPressedCallback(key, x, y);
}

// This function should just call the HID manager
void mouseEventCallback(int button, int state, int x, int y) {
	gHIDManager->mouseEventCallback(button, state, x, y);
}

// Here we begin.
// Start the FreeGLUT window manager
int main(int argc, char **argv) {

	// Init log system
	// Init config manager
	gRessourcesManager = std::make_shared<Ressources::Manager>();
	gRessourcesManager->init();
	gConfigManager = std::make_shared<Ressources::Config>();
	gConfigManager->init(gRessourcesManager);

	// Init HID manager
	gHIDManager = std::make_shared<HID::Manager>();
	gHIDManager->init(gConfigManager);

	// Init GLUT and create window
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("IGR202");

	// Init OpenGL context
	gl_init_context();

	// Register callbacks
	glutKeyboardFunc(keyPressedCallback);
	glutMouseFunc(mouseEventCallback);
	glutSpecialFunc(specialKeyPressedCallback);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMotionFunc(motion);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
