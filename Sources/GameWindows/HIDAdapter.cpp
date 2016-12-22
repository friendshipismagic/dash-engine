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

#include "GameWindows/Window.h"
#include "GameWindows/HID.h"

#include "GameWindows/HIDAdapter.h"

namespace HID {
	Keyboard_Adapter::init() {
		// TODO: Actually does not do anything
	}

	void Keyboard_Adapter::connect_window(
			std::shared_ptr<GameWindows::Window> win) {
		// Add only if it does not already exists
		if(std::find(reg_wins.begin(), reg_wins.end(), win) == reg_wins.end())
			reg_wins.push_back(win);
	}
}
