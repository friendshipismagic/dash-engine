/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <sstream>

namespace ECS {
	class Entity {
		public:
			// Entity generator
			static Entity generate();

			// Just one need, test equality
			bool operator==(Entity const& id) const;

			// For logging purposes
			//std::ostream& operator<<(std::ostream &out, const Entity &t);
	};
}
