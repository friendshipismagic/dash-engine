/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <memory>

#include "GameWindows/HIDAdapter.h"

#include "ECS/Components/Component_input.h"

namespace ECS {
	Component_input::Component_input(std::shared_ptr<HID::HIDAdapter> adapter) {
		this->adapter = adapter;
	}

	void Component_input::parse_event(std::string event) {
		input_events.push_back(event);
	}
}
