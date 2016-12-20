/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "easylogging++.h"
#include "GameWindows/Window.h"
#include "GameWindows.h"

namespace GameWindows {
	void Manager::init(std::shared_ptr<Ressources::Config> configManager) {
		// Get Config Manager
		gConfigManager = configManager;

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
	}

	void Manager::stop() {
		SDL_Quit();
	}

	int Manager::create_game_window(std::string title) {
		// Find a suitable ID (non-zero for safety) and instanciate a
		// GameWindows::Window object
		// TODO
		std::shared_ptr<GameWindows::Window> win =
			std::make_shared<GameWindows::Window>();
		win->init(max_id, title, 800, 600);
		windowslist.push_back(win);
		max_id++;
		return max_id-1;
	}
}
