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
#include <GL/glew.h>

namespace Ressources {
	class UShader {
		public:
			// Default constructor
			UShader(std::string name, GLenum shaderType, std::string filepath);

			// Get the filepath of the shader
			std::string get_name() { return filepath; };

			// Shader loader
			int load();

			// Shader unloader
			void unload();

			// Shader status
			int status();

			// Shader compile
			int compile();

			// Shader link to Program
			void link(GLuint);

		private:
			// Name of shader
			std::string name;
			// Shader ID when created
			GLuint shaderID;
			// File path of shader
			std::string filepath;
			// Source of shader (array)
			GLchar** ss;
			// Length of source array
			int len;
	};
}
