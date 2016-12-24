/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "ECS/Entity.h"
#include <vector>

namespace ECS {
	// /!\ This is a pure abstract class in which every component should
	// inherit!
	class Component {
		public:
			// Connect
			virtual void connect_entity(ECS::Entity);

		private:
			// List of connected entities
			std::vector<ECS::Entity> list_of_entities;
	};
}
