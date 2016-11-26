/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include "HID.h"

namespace HID {
	void Manager::init() {
		//TODO: Load the key binding
	}

	void Manager::keyPressedCallback(unsigned char key, int x, int y) {
		// TODO: Call the right observer depending on keybinding
	}

	void Manager::specialKeyPressedCallback(int key, int x, int y) {
		// TODO: Call the right observer depending on keybinding
	}

	void Manager::mouseEventCallback(int button, int state, int x, int y) {
		// TODO: Call the right observer depending on keybinding
	}
}
