/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <string>
#include <cstdint>
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

		// Limit to core profile to disable deprecated functions
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
				SDL_GL_CONTEXT_PROFILE_CORE);

		// Took from
		// http://stackoverflow.com/questions/13826150/sdl2-opengl3-how-to-initialize-sdl-inside-a-function
		// set the depth buffer to 24 bits
		// you may need to change this to 16 or 32 for your system
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Set window flags
		// Mandatory flag is SDL_WINDOW_OPENGL
		Uint32 flags = SDL_WINDOW_OPENGL |
			SDL_WINDOW_SHOWN |
			SDL_WINDOW_BORDERLESS |
			SDL_WINDOW_MAXIMIZED |
			SDL_WINDOW_INPUT_GRABBED |
			SDL_WINDOW_INPUT_FOCUS |
			SDL_WINDOW_MOUSE_FOCUS |
			SDL_WINDOW_ALLOW_HIGHDPI |
			SDL_WINDOW_MOUSE_CAPTURE;

		// Now create a window
		// XXX: Bad guy, you shouldn't do that
		{ // Create a local scope to be sure test will never be used again
			std::unique_ptr<SDL_Window, sdl2::SDL_Deleter> test(
					SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, width, height, flags),
					sdl2::SDL_Deleter());

			lWindow = std::move(test);
		}
		LOG_IF(lWindow == nullptr, ERROR) << "Cannot create a new window";

		// Init pure GL part of context
		LOG(DEBUG) << "Initializing OpenGL context";
		gl_init_context();
		LOG(DEBUG) << "OpenGL context ready";
	}

	// OpenGL context creation
	void Window::gl_init_context() {
		// Call a context creation
		opengl_context = SDL_GL_CreateContext((SDL_Window*) lWindow.get());

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
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// Clear back buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// Swap back and front buffers
		swapBuffers();
	}

	void Window::stop() {
		SDL_GL_DeleteContext(opengl_context);
		// TODO: explicitly destruct the unique_ptr ? SDL_DestroyWindow(lWindow);
	}

	void Window::swapBuffers() {
		SDL_GL_SwapWindow(lWindow.get());
	}
}
