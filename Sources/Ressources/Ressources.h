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
#include <GL/glew.h>

namespace Ressources {
	class Manager {
		public:
			// Default constructor, should not do anything
			Manager() {};
			// Default destructor, should not do anything
			~Manager() {};

			// Initializer
			void init();

			// Config file ressource, it should look for the right config file
			// and return its path
			std::string getConfigFilePath();

			// Shaders file ressource, it should look for the right shader file
			// path and return it
			std::string getShadersFolderPath();

			// Models file ressource, it should look for the right model file
			// path and return it
			std::string getModelsFolderPath();

			// Default Shader Program to use when importing
			GLuint getDefaultShaderProgram() { return defaultProgram; };
			void setDefaultShaderProgram(GLuint p) { this->defaultProgram = p; };

		private:
			GLuint defaultProgram = 0;
	};
}
