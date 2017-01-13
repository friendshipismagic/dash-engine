/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <vector>

#include "Ressources/Mesh.h"

namespace Ressources {
	void init(std::vector<Vertex> vertices,
			std::vector<GLuint> indices,
			std::vector<Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		// Now set the VAO, VBO and EBO
		// Create buffers/arrays
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		// Load data in VAO/VBO
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
				&this->vertices[0], GL_STATIC_DRAW);  

		// Now use EBO to put VBO Index
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				this->indices.size() * sizeof(GLuint), &this->indices[0],
				GL_STATIC_DRAW);

		// Set the vertex attribute pointers
		// Vertex Positions
		glEnableVertexAttribArray(0);	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (GLvoid*)0);
		// Vertex Normals
		glEnableVertexAttribArray(1);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		// Vertex Texture Coords
		glEnableVertexAttribArray(2);	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

		// Unbind all to get back to previous openGL state
		glBindVertexArray(0);
	}
}
