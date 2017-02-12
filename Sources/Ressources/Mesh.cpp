/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <vector>
#include <iostream>
#include <sstream>

#include "Ressources/Mesh.h"

namespace Ressources {
	// Parts of this code are based on learnopengl website (CC public domain)
	void Mesh::init(std::vector<Vertex> vertices,
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

		// Load VAO
		glBindVertexArray(this->VAO);
		// Copy vertices to VBO
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Vertex Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(1);
		// Vertex Texture Coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
		glEnableVertexAttribArray(2);

		// Unbind the VAO to restore initial OpenGL context
		glBindVertexArray(0);
	}

	void Mesh::render(GLuint shaderProgram) {
		// Set Shader Program to use
		glUseProgram(shaderProgram);

        // Bind appropriate textures
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        for(GLuint i=0; i<this->textures.size(); i++)
        {
			// Active proper texture
            glActiveTexture(GL_TEXTURE0 + i);
            // Retrieve texture number (the N in diffuse_textureN)
			// Using same conventions as learopengl.com
			// So also using their code here :)
			std::stringstream ss;
			std::string number;
            std::string name = this->textures[i].type;
            if(name == "texture_diffuse")
                ss << diffuseNr++; // Transfer GLuint to stream
            else if(name == "texture_specular")
                ss << specularNr++; // Transfer GLuint to stream
            number = ss.str(); 
            // Now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shaderProgram,
						(name + number).c_str()), i);
            // And finally bind the texture
            glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
        }
        
        // Also set each mesh's shininess property to a default value
        glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"),
				16.0f);

        // Draw mesh
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Always good practice to set everything back to defaults once configured.
        for (GLuint i = 0; i < this->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
	}
}
