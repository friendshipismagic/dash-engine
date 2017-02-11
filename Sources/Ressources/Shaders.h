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
#include "Ressources/UShader.h"

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
			// TODO
			void list_shaders();

			// Select shaders names to use in a vector
			// Return the Shader Program ID
			GLuint make_shader_program(std::vector<std::string>);

		private:
			// Add a shader
			void add_shaders(std::vector<std::string>);

			// Folder path of the shaders
			std::string shaders_folder;
			// Loaded shaders
			std::vector<std::shared_ptr<Ressources::UShader>> shaders_list;
			// Shader programs
			std::vector<GLuint> program_shaders;
	};
}
