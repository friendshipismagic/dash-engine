/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "ECS/Component.h"

namespace ECS {
	class Component_input: public Component {
		public:
			// Default construtor, to use (external code). There will not be
			// any init method
			Component_input();
			// Default destructor, to use (external code). There will not be
			// any stop method
			~Component_input();

			// Update the values in the component
			void update();
	};
}
