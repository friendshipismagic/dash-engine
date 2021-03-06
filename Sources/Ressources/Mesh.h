/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>

#include "Ressources/Shaders.h"
#include "assimp/scene.h"

namespace Ressources {
	struct Vertex {
		// Position
		glm::vec3 Position;
		// Normal
		glm::vec3 Normal;
		// TexCoords
		glm::vec2 TexCoords;
	};

	class Mesh {
		public:
			// Initializer, taking vertices, indices
			Mesh(std::vector<Vertex>,
					std::vector<GLuint>,
					GLuint shaderProgram);

			// Render the mesh itself
			void render();
		private:
			// The mesh itself
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;
			// The shader program associated to it
			GLuint shaderProgram;
			// OpenGL Objects
			GLuint VAO, VBO, EBO;

	};
}
