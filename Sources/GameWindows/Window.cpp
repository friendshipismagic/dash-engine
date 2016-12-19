/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <string>

namespace GameWindows {
	void Window::init(int ID, string title, int width, int height) {
		lWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN,
				SDL_WINDOW_RESIZABLE);
		LOG_IF(!lwindow, ERROR) << "Cannot create a new window";
	}
}
