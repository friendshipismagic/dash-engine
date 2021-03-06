/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "Ressources/Config.h"
#include "GameWindows/HIDAdapter.h"

namespace HID {
	class Manager {
		public:
			// Default constructor, should not do anything
			Manager() {};
			// Default destructor, should not do anything
			~Manager() {};

			// Initializer, if needed
			void init(std::shared_ptr<Ressources::Config>);

			// Check for events
			void check_for_inputs();

			// Connect to Adapter
			void connect_adapter(std::shared_ptr<HID::HIDAdapter>);
		private:
			// Key binding
			std::map<SDL_Scancode, std::string> keymap;
			// List of adapters
			std::vector<std::shared_ptr<HID::HIDAdapter>> adapter_list;
	};
}
