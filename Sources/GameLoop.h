/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <memory>
#include "GameWindows/HID.h"

// TODO: Should I put it in a namespace?

class GameLoop {
	public:
		// Default initializer, should not do anything
		GameLoop () {};
		// Default destructor, should not do anything
		~GameLoop () {};

		// Initializer, needs the main time step
		void init(int);

		// Connect the HID Manager
		void connect_HID(std::shared_ptr<HID::Manager>);

		// Enter the loop :)
		void loop();
	private:
		// Time step
		int main_ts;
		// Main HID Manager
		std::shared_ptr<HID::Manager> lHIDManager;
};
