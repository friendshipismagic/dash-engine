/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include "ECS/Entity.h"

#include <sstream>

namespace ECS {
	std::ostream& operator<<(std::ostream &os, const Entity &e) {
		//TODO
		os << "TODO";
		return os;
	}

	bool Entity::operator==(Entity const& id) const {
		//TODO
		return true;
	}
}
