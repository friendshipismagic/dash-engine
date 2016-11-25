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

// Keyboard callback.
// Called when a basic key is pressed
void keyboard(unsigned char key, int x, int y) {
}

// Mouse callback.
// Called when a mouse event happens
void mouse(int button, int state, int x, int y) {
}

// Motion callback.
// Called when a mouse drag happens
void motion(int x, int y) {
}

// Special inputs callback.
// Called when a special key is pressed
void specialinput(int key, int x, int y) {
}

// Idle callback.
// Called when nothing else is called
void idle() {
}

// Here we begin.
// Start the FreeGLUT window manager
int main(int argc, char **argv) {

	// Init GLUT and create window
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("IGR202");

	// Register callbacks
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(specialinput);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
