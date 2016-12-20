/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <string>
#include <SDL2/SDL.h>

// SDL Deleter for smart pointers
// Thanks to http://swarminglogic.com/jotting/2015_05_smartwrappers
namespace sdl2 {
	struct SDL_Deleter {
		void operator()(SDL_Surface*  ptr) {
			if (ptr != nullptr) SDL_FreeSurface(ptr);
		}
		void operator()(SDL_Texture*  ptr) {
			if (ptr != nullptr) SDL_DestroyTexture(ptr);
		}
		void operator()(SDL_Renderer* ptr) {
			if (ptr != nullptr) SDL_DestroyRenderer(ptr);
		}
		void operator()(SDL_Window* ptr) {
			if (ptr != nullptr) SDL_DestroyWindow(ptr);
		}
		void operator()(SDL_RWops* ptr) {
			if (ptr != nullptr) SDL_RWclose(ptr);
		}
	};
}

namespace GameWindows {
	class Window {
		public:
			// Default Constructor, should just initalize lWindow to nullptr
			Window() : lWindow(nullptr) {};
			// Default destructor, should not do anything
			~Window() {};

			// Initializer, needs a unique ID and a title
			void init(int ID, std::string title, int width, int height);

			// Destructor, removes context and so on
			void stop();

			// ID getter
			int getID() const {return ID;};

			// Attach an adapter to plug to the HID Manager
			void attach(); // TODO: Adapters

			// Detach an adapter
			void detach(); // TODO: Adapters
		private:
			// OpenGL Context initializer
			void gl_init_context();

			// Window ID
			int ID;
			// SDL Window
			std::unique_ptr<SDL_Window, sdl2::SDL_Deleter> lWindow;
			// OpenGL Context for window
			SDL_GLContext opengl_context;
			// Width and Height
			int width = 800;
			int height = 600;
	};
}
