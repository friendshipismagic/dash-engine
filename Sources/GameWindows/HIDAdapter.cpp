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
	void HIDAdapter::init() {
		// TODO: Actually does not do anything
	}

	void HIDAdapter::connect_window(
			std::shared_ptr<GameWindows::Window> win) {
		// Add only if it does not already exists
		if(std::find(reg_wins.begin(), reg_wins.end(), win) == reg_wins.end())
			reg_wins.push_back(win);
	}

	void HIDAdapter::add_events(
			std::vector<std::string> events) {
		// Add only if it does not already exists
		for(auto event: events)
			if(std::find(reg_events.begin(), reg_events.end(), event) == reg_events.end())
				reg_events.push_back(event);
	}

	void HIDAdapter::remove_events(
			std::vector<std::string> events) {
		for(auto event: events)
			reg_events.erase(std::remove(
						reg_events.begin(), reg_events.end(), event),
					reg_events.end());
	}

	void HIDAdapter::parse_event(std::string event) {
		// Now event should be sent to the windows that registered to it
		for(auto win: reg_wins) {
			// First check event is to be treated
			if(std::find(reg_events.begin(), reg_events.end(), event) != reg_events.end())
				win->parse_event(event);
		}
	}

}
