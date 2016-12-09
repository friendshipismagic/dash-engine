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
#include <string>
#include <iostream>

#include "Ressources/Config.h"

#include "HID.h"

namespace HID {
	void Manager::init(std::shared_ptr<Ressources::Config> localConfig) {
		// Load the key binding
		keymap = localConfig->get_keymap();
	}

	void Manager::keyPressedCallback(unsigned char key, int x, int y) {
		// TODO: Call the right observer depending on keybinding
		std::cout << "Key " << key << " pressed, corresponds to "
				  << keymap[key] << " event" << std::endl;
	}

	void Manager::specialKeyPressedCallback(int key, int x, int y) {
		// TODO: Call the right observer depending on keybinding
	}

	void Manager::mouseEventCallback(int button, int state, int x, int y) {
		// TODO: Call the right observer depending on keybinding
	}
}
