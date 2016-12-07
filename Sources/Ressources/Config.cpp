/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <string>
#include <memory>

#include "Config.h"

namespace Ressources {
	void Config::init(std::shared_ptr<Manager> localManager) {
		// Get the full file path from the ressource manager
		this->filepath = localManager->getConfigFilePath();

		// If the file does not exist, it should be created with a default
		// configuration

		// TODO: Load the file and call the parser
		
		// TODO: put the parsed in variable
	}
}
