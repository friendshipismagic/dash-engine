/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <memory>

#include "Ressources/Ressources.h"

#include "Ressources/Shaders.h"

namespace Ressources {
	void Shaders::init(std::shared_ptr<Ressources::Manager> localManager) {
		// Get the shaders folder path
		this->shaders_folder = localManager->getShadersFolderPath();
	}
}
