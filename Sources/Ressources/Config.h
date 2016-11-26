/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <String>

namespace Ressources {
	class Config {
		public:
			// Default constructor, should not do anything
			Config() {};
			// Default destructor, should not do anything
			~Config() {};

			// Initializer
			void init();

			// Better initializer, taking an URI to the config file
			void init(std::string filepath);
	};
}