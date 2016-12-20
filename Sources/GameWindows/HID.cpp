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
#include <SDL2/SDL.h>

#include "Ressources/Config.h"

#include "HID.h"

namespace HID {
	void Manager::init(std::shared_ptr<Ressources::Config> localConfig) {
		// Load the key binding
		keymap = localConfig->get_keymap();
	}

	void Manager::check_for_inputs() {
		// TODO: Treat the whole queue with corresponding keybinding
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			// Events can be :
			// - Mouse related :
			// SDL_MOUSEMOTION, SDL_MOUSEBUTTONDOWN/UP, SDL_ACTIVEEVENT
			//
			// - Keyboard related :
			// SDL_KEYDOWN/UP, 
			//
			// - Joystick related :
			// SDL_JOYAXISMOTION, SDL_JOYBALLMOTION, SDL_JOYHATMOTION
			// SDL_JOYBUTTONDOWN/UP
			//
			// - Window related :
			// SDL_QUIT, SDL_SYSWMEVENT , SDL_VIDEORESIZE , SDL_VIDEOEXPOSE
			//
			// - Custom event :
			// SDL_USEREVENT
		}
	}
}
