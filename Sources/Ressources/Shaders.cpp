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
#include "Ressources/UShader.h"

#include "Ressources/Shaders.h"

namespace Ressources {
	void Shaders::init(std::shared_ptr<Ressources::Manager> localManager) {
		// Get the shaders folder path
		this->shaders_folder = localManager->getShadersFolderPath();
	}

	GLuint Shaders::make_shader_program(std::vector<std::string> fns) {
		// Make an empty program
		GLuint shaderProgram;
		shaderProgram = glCreateProgram();

		// Add the shaders in list of shader if they do not already exist
		add_shaders(fns);

		// Translate filenames to shaders pointers
		for(std::string fn: fns) {
			for(std::shared_ptr<Ressources::UShader> shader: shaders_list)
				if(shader->get_name().find(fn) != std::string::npos) {
					// Found the shader, link it
					shader->link(shaderProgram);
				}
		}

		program_shaders.push_back(shaderProgram);
		// Set GL to use the program
		glUseProgram(shaderProgram);

		// TODO: Maybe delete the shaders after program linking
		// if they're not used anymore with glDeleteShader(shaderID);

		// Now return program ID
		return shaderProgram;
	}

	void Shaders::add_shaders(std::vector<std::string> fns) {
		for(std::string fn: fns) {
			// Check if file already exists
			bool alreadyMade = false;
			for(std::shared_ptr<Ressources::UShader> shader: shaders_list)
				alreadyMade |= (shader->get_name() == fn);

			// Add it otherwize
			if(!alreadyMade) {
				std::string extension = fn.substr(fn.find_last_of(".") + 1);
				// For a fragment shader
				GLenum shaderType;
				if(extension == "frag")
					shaderType = GL_FRAGMENT_SHADER;
				else if(extension == "vert")
					shaderType = GL_VERTEX_SHADER;
				else {
					// TODO Log the error
					return;
				}
				// Make the shader itself
				std::shared_ptr<Ressources::UShader> localShader =
					std::make_shared<Ressources::UShader>(
							fn, shaderType, shaders_folder + fn);
				// Load it to memory
				int success = localShader->load();
				// TODO Check if loading, compiling successfull
				// Compile it
				success = localShader->compile();

				shaders_list.push_back(localShader);
			}
		}
	}
}
