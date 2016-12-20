/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>

#include "easylogging++.h"
#include "GameWindows/Window.h"

namespace GameWindows {
	void Window::init(int ID, std::string title, int width, int height) {
		// Set the opengl context version to GL 3.2
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		// Turn on double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		// sync buffer swap with monitor's vertical refresh rate
		SDL_GL_SetSwapInterval(1);

		// Took from
		// http://stackoverflow.com/questions/13826150/sdl2-opengl3-how-to-initialize-sdl-inside-a-function
		// set the depth buffer to 24 bits
		// you may need to change this to 16 or 32 for your system
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Now create a window
		{ // Create a local scope to be sure test will never be used again
			std::unique_ptr<SDL_Window, sdl2::SDL_Deleter> test(
					SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL),
					sdl2::SDL_Deleter());

			lWindow = std::move(test);
		}
		//LOG_IF(lWindow == nullptr, ERROR) << "Cannot create a new window";

		// Init pure GL part of context
		LOG(DEBUG) << "Initializing OpenGL context";
		gl_init_context();
		LOG(DEBUG) << "OpenGL context ready";
	}

	// OpenGL context creation
	void Window::gl_init_context() {
		// Enable experimental drivers
		glewExperimental = GL_TRUE;

		// Init GLEW
		GLenum err = glewInit();
		// Oops, GLEW failed to start
		LOG_IF(err != GLEW_OK, ERROR) << "GLEW Fatal error: "
			<< glewGetErrorString(err);

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

	void Window::stop() {
		SDL_GL_DeleteContext(opengl_context);
		// TODO: explicitly destruct the unique_ptr ? SDL_DestroyWindow(lWindow);
	}
}
