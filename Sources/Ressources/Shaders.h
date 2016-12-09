/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <memory>
#include <string>

#include "Ressources/Ressources.h"

namespace Ressources {
	class Shaders {
		public:
			// Default constructor, should not do anything
			Shaders() {};
			// Default destructor, should not do anything
			~Shaders() {};

			// Initializer, taking a ressource manager to get the shader folder
			void init(std::shared_ptr<Ressources::Manager>);

			// List shaders
			void list_shaders();

			//////////////////////////
			// Per-shader functions //
			//////////////////////////

			// Shader loader
			void shader_load();

			// Shader unloader
			void shader_unload();

			// Shader status
			int shader_status();

			// Shader compile
			void shader_compile();

			// Shader link
			void shader_link();

		private:
			// Folder path of the shaders
			std::string shaders_folder;
	};
}
