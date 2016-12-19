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

namespace GameWindows {
	class Window {
		public:
			// Default Constructor, should not do anything
			Window() {};
			// Default destructor, should not do anything
			~Window() {};

			// Initializer, needs a unique ID and a title
			void init(int ID, string title, int width, int height);

			// Attach an adapter to plug to the HID Manager
			void attach(); // TODO: Adapters

			// Detach an adapter
			void detach(); // TODO: Adapters
		private:
			// Window ID
			int ID;
			// SDL Window
			SDL_Window* lWindow;
			// Width and Height
			int width = 800
			int height = 600;
	};
}
