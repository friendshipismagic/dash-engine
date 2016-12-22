/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <memory>
#include <algorithm>
#include <vector>

#include "GameWindows/Window.h"
#include "GameWindows/HID.h"

#include "GameWindows/HIDAdapter.h"

namespace HID {
	void Keyboard_Adapter::init() {
		// TODO: Actually does not do anything
	}

	void Keyboard_Adapter::connect_window(
			std::shared_ptr<GameWindows::Window> win) {
		// Add only if it does not already exists
		if(std::find(reg_wins.begin(), reg_wins.end(), win) == reg_wins.end())
			reg_wins.push_back(win);
	}

	void Keyboard_Adapter::connect_HID(
			std::shared_ptr<HID::Manager> manager) {
		// Add only if it does not already exists
		if(std::find(reg_hid.begin(), reg_hid.end(), manager) == reg_hid.end())
			reg_hid.push_back(manager);
	}

	void Keyboard_Adapter::add_events(
			std::vector<std::string> events) {
		// Add only if it does not already exists
		for(auto event: events)
			if(std::find(reg_events.begin(), reg_events.end(), event) == reg_events.end())
				reg_events.push_back(event);
	}


	void Keyboard_Adapter::remove_events(
			std::vector<std::string> events) {
		for(auto event: events)
			reg_events.erase(std::remove(
						reg_events.begin(), reg_events.end(), event),
					reg_events.end());
	}

}
