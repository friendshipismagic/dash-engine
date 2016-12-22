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
#include <vector>

#include "GameWindows/Window.h"
#include "GameWindows/HID.h"
#include "GameWindows/HIDAdapter.h"

namespace GameWindows {
	class Manager {
		public:
			// Default constructor, should not do anything
			Manager() {};
			// Default destructor, should not do anything
			~Manager() {};

			// Initializer
			void init(std::shared_ptr<Ressources::Config>);

			// Destructor, call SDL_quit
			void stop();

			// Create a new window, returning its ID
			int create_game_window(std::string title);

			// Destroy a window with specified ID
			void close_game_window(int id);

			// Instanciate a new adapter
			int create_adapter(std::vector<std::string> events);

			// Connect an adapter with a window
			void connect_adapter(int adapter, int win);

		private:
			// List of currently in-use windows
			std::vector<std::shared_ptr<GameWindows::Window>> windowslist;
			// Global HID Manager
			std::shared_ptr<Ressources::Config> gConfigManager;
			// Global HID Manager
			std::shared_ptr<HID::Manager> gHIDManager;
			// Adapters
			std::vector<std::shared_ptr<HID::HIDAdapter>> adapterslist;
			// Current max ID for windows
			int win_max_id = 0;
			// Current max ID for adapters
			int ada_max_id = 0;
	};
}
