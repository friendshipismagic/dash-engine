/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <SDL.h>

#include "GameWindows.h"

namespace GameWindows {
	void Manager::init() {
		// Init HID manager
		LOG(DEBUG) << "Initializing HID manager";
		gHIDManager = std::make_shared<HID::Manager>();
		gHIDManager->init(gConfigManager);
		LOG(INFO) << "HID manager online";

		// Init SDL
		bool sdl_failure = SDL_Init(SDL_INIT_VIDEO) < 0;
		LOG_IF(sdl_failure, FATAL) << "Could not initalize"
			<< "SDL Error: " << SDL_GetError();
		if(sdl_failure)
			return;
		// TODO: Throw exception

		// Init OpenGL context
		LOG(DEBUG) << "Initializing OpenGL context";
		gl_init_context();
		LOG(DEBUG) << "OpenGL context ready";
	}

	int Manager::create_game_window() {
		// Find a suitable ID (non-zero for safety) and instanciate a
		// GameWindows::Window object
		// TODO
	}
}
