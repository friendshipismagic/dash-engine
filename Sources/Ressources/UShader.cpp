/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <GL/glew.h>

#include "easylogging++.h"

#include "Ressources/UShader.h"

namespace Ressources {
	UShader::UShader(std::string name, GLenum shaderType, std::string filepath) {
		shaderID = glCreateShader(shaderType);
		this->filepath = filepath;
		this->name = name;
	}

	int UShader::load() {
		std::ifstream shaderFile;
		// ensures ifstream objects can throw exceptions:
		shaderFile.exceptions(std::ifstream::badbit);
		try 
		{
			// Open file
			shaderFile.open(filepath);
			std::stringstream shaderStream;
			// Read file's buffer contents into stream
			shaderStream << shaderFile.rdbuf();
			// close file handlers
			shaderFile.close();
			// Convert stream into GLchar array
			shaderSource = shaderStream.str();
		}
		catch(std::ifstream::failure e)
		{
			LOG(ERROR) << "Shader file not succesfully read";
		}

		const GLchar* shaderCodeChar = shaderSource.c_str();
		// Attach the sources to the shader object
		glShaderSource(shaderID, 1, &shaderCodeChar, NULL);

		return 0;
	}

	int UShader::status() {
		// TODO
		return 0;
	}

	int UShader::compile() {
		// Just compile !
		glCompileShader(shaderID);
		
		// Check it's ok
		GLint compiled;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
		// TODO if compiled then it's ok, otherwize throw an exception !!
		if(!compiled) {
			GLint blen = 0;
			GLsizei slen = 0;

			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &blen);

			if(blen > 1) {
				GLchar* compiler_log = (GLchar*)malloc(blen); // TODO ARGH
				glGetShaderInfoLog(shaderID, blen, &slen, compiler_log);
				// TODO error logs are in compiler_log
				free(compiler_log);
			}
			return -1;
		}
		return 0;
	}

	void UShader::link(GLuint shaderProgram) {
		glAttachShader(shaderProgram, shaderID);
		// TODO Check for linking issue as for compilation
	}

}
