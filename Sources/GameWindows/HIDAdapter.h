/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <string>
#include <memory>
#include <vector>

namespace HID {
	class Keyboard_Adapter {
		public:
			// Default constructor, should not do anything
			Keyboard_Adapter() {};
			// Default destructor, should not do anything
			~Keyboard_Adapter() {};

			// Initalizer
			void init();

			// Connect to Window
			void connect_window(std::shared_ptr<GameWindows::Window>);

			// Connect to HID manager
			void connect_HID(std::shared_ptr<HID::Manager>);

			// Add events to catch
			void add_events(std::vector<std::string>);

			// Remove events to catch
			void remove_events(std::vector<std::string>);
		private:
			// List of registered windows
			std::vector<std::shared_ptr<GameWindows::Window>> reg_wins;
			// List of registered HID managers
			std::vector<std::shared_ptr<HID::Manager>> reg_hid;
			// List of registered events to catch
			std::vector<std::string> reg_events;
	};
}