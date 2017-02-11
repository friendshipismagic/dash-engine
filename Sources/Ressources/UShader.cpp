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

#include "Ressources/UShader.h"

namespace Ressources {
	UShader::UShader(std::string name, GLenum shaderType, std::string filepath) {
		shaderID = glCreateShader(shaderType);
		this->filepath = filepath;
		this->name = name;
	}

	int UShader::load() {
		// Open file
		std::ifstream file(filepath.c_str(), std::ios::in);
		if(!file) return -1;

		// Get file length to store to array
		file.seekg(0, std::ios::end);
		len = file.tellg();
		file.seekg(0, std::ios::beg);
		if(len==0) return -2;

		// Reserve memory to array
		*ss = (GLchar*) new char[len+1];
		if(*ss == 0) return -3;

		// Get characters from file
		*ss[len] = 0;
		unsigned int i = 0;
		while(file.good()) {
			*ss[i] = file.get();
			if(!file.eof()) i++;
		}
		*ss[i] = 0;

		// Close file
		file.close();

		// Attach the sources to the shader object
		glShaderSource(shaderID, 1, ss, &len);

		return 0;
	}

	void UShader::unload() {
		if(*ss !=0)
			delete[] *ss;

		*ss = 0;
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
		glGetShaderInfoLog(shaderID, GL_COMPILE_STATUS, &compiled);
		// TODO if compiled then it's ok, otherwize throw an exception !!
		if(!compiled) {
			GLint blen = 0;
			GLsizei slen = 0;

			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &blen);

			if(blen > 1) {
				GLchar* compiler_log = (GLchar*)malloc(blen); // TODO ARGH
				glGetInfoLog(shaderID, blen, &slen, compiler_log);
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
