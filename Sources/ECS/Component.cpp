/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <vector>
#include <algorithm>

#include "ECS/Entity.h"
#include "easylogging++.h"

#include "ECS/Component.h"

namespace ECS {
	void Component::connect_entity(ECS::Entity entity) {
		if(std::find(list_of_entities.begin(), list_of_entities.end(), entity)
				== list_of_entities.end()) {
			LOG(DEBUG) << "Registering new entity, ID: " << entity;
			list_of_entities.push_back(entity);
		}
	}
}
