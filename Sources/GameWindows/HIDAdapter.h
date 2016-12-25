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

#include "ECS/Components/Component_input.h"

#include "GameWindows/Window.h"

namespace HID {
	class HIDAdapter {
		public:
			// Default constructor, should not do anything
			HIDAdapter() {};
			// Default destructor, should not do anything
			~HIDAdapter() {};

			// Initalizer
			void init(int);

			// Connect a component
			void connect_component(std::shared_ptr<ECS::Component_input>);

			// Add events to catch
			void add_events(std::vector<std::string>);

			// Remove events to catch
			void remove_events(std::vector<std::string>);

			// Add an event to catch immediatly
			// WARNING: To be used only by the HID Manager
			void parse_event(std::string);

			// Getter
			int getID() const {return ID;};
		private:
			// ID
			int ID = 0;

			// List of registered windows
			std::vector<std::shared_ptr<ECS::Component_input>> reg_comp;

			// List of registered events to catch
			std::vector<std::string> reg_events;
	};
}
