/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <memory>
#include "GameWindows/HID.h"

#include "GameLoop.h"

void GameLoop::init(int ts) {
	// Update the main timestep
	main_ts = ts;
}

void GameLoop::connect_HID(std::shared_ptr<HID::Manager> gHIDManager) {
	// Connect the HID Manager
	lHIDManager = gHIDManager;
}

void GameLoop::loop() {

}
