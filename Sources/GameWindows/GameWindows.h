/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "HID.h"

namespace GameWindows {
	class Manager {
		public:
			// Default constructor, should not do anything
			Manager() {};
			// Default destructor, should not do anything
			~Manager() {};

			// Initializer
			void init();

			// Create a new window, returning its ID
			int create_game_window();

			// Destroy a window with specified ID
			void close_game_window(int id);

		private:
			// List of currently in-use windows
			std::vector<GameWindows::Window> windowslist;
			// Global HID Manager
			std::shared_ptr<HID::Manager> gHIDManager;
	};
}
