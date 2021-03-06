/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <memory>
#include <map>
#include <algorithm>
#include <SDL2/SDL.h>

#include "easylogging++.h"
#include "Ressources/Config.h"
#include "GameWindows/HIDAdapter.h"

#include "HID.h"

namespace HID {
	void Manager::init(std::shared_ptr<Ressources::Config> localConfig) {
		// Load the key binding
		LOG(DEBUG) << "Loading Key map";
		keymap = localConfig->get_keymap();
	}

	void Manager::check_for_inputs() {
		// TODO: Treat the whole queue with corresponding keybinding
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			// List of events can be found on:
			// https://wiki.libsdl.org/SDL_EventType
			switch(event.type) {
				case SDL_KEYDOWN:
					for(auto adapter: adapter_list)
						adapter->parse_event(keymap[event.key.keysym.scancode]);
					LOG(DEBUG) << "User pressed: "
						<< SDL_GetScancodeName(event.key.keysym.scancode);
					break;
			}
			// Event to use is "HID::HIDAdapter::parse_event(std::string event)"
		}
	}

	void Manager::connect_adapter(std::shared_ptr<HIDAdapter> adapter) {
		// Add only if it does not already exists
		LOG(DEBUG) << "Connecting to adapter";
		if(std::find(adapter_list.begin(), adapter_list.end(), adapter)
				== adapter_list.end())
			adapter_list.push_back(adapter);
	}
}
