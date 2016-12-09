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
#include <map>
#include <memory>

#include "Ressources/Ressources.h"

namespace Ressources {
	class Config {
		public:
			// Default constructor, should not do anything
			Config() {};
			// Default destructor, should not do anything
			~Config() {};

			// Initializer, taking a ressource manager to get the config file
			void init(std::shared_ptr<Ressources::Manager>);

			// Generate a default config file with only mandatory parameters
			void generate_default_config();

			// Get keymap
			std::map<char, std::string> get_keymap();

		private:
			std::string filepath;
			std::map<std::string, std::string> parameters;
	};
}
