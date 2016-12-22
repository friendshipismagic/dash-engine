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

#include "GameWindows/Window.h"

namespace HID {
	class HIDAdapter {
		public:
			// Default constructor, should not do anything
			HIDAdapter() {};
			// Default destructor, should not do anything
			~HIDAdapter() {};

			// Initalizer
			void init();

			// Connect to Window
			void connect_window(std::shared_ptr<GameWindows::Window>);

			// Add events to catch
			void add_events(std::vector<std::string>);

			// Remove events to catch
			void remove_events(std::vector<std::string>);

			// Add an event to catch immediatly
			// WARNING: To be used only by the HID Manager
			void parse_event(std::string);

		private:
			// List of registered windows
			std::vector<std::shared_ptr<GameWindows::Window>> reg_wins;

			// List of registered events to catch
			std::vector<std::string> reg_events;
	};
}
