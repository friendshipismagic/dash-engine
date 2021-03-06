/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "easylogging++.h"

#include "Ressources/Ressources.h"

#include "Ressources/Models.h"

namespace Ressources {
	void Models::init(std::shared_ptr<Ressources::Manager> fm, std::string fn) {
		// As use ressource manager only once, we don't need to keep it
		this->directory = fm->getModelsFolderPath();
		this->filepath = directory + fn;
		defaultShader = fm->getDefaultShaderProgram();

		// Taken from the usage doc
		importer = std::make_shared<Assimp::Importer>();

		// Read the file and do some postprocessing on it, the postprocessing
		// should be configured in the config: TODO
		scene = importer->ReadFile(filepath,
				aiProcess_CalcTangentSpace      |
				aiProcess_GenNormals            |
				aiProcess_Triangulate           |
				aiProcess_JoinIdenticalVertices |
				aiProcess_SortByPType);

		// If import failed, log it
		if(!scene ||
				scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
				!scene->mRootNode)
			LOG(ERROR) << "Cannot load scene named " << fn;

		// Import Meshes by recursively browsing throught the tree
		processNode(scene->mRootNode, scene);
	}

	void Models::render_scene() {
		for(Ressources::Mesh mesh: meshes)
			mesh.render();
	}

	void Models::processNode(aiNode* node, const aiScene* scene) {
		// Process all the node's meshes (if any)
		for(GLuint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
			this->meshes.push_back(this->processMesh(mesh, scene));			
		}
		// Then do the same for each of its children
		for(GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}
	}

	Ressources::Mesh Models::processMesh(aiMesh* mesh, const aiScene* scene) {
		// Data to fill
		std::vector<Ressources::Vertex> vertices;
		std::vector<GLuint> indices;

		// Walk through each of the mesh's vertices
		for(GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Ressources::Vertex vertex;
			// We declare a placeholder vector since assimp uses its own vector
			// class that doesn't directly convert to glm's vec3 class so we
			// transfer the data to this placeholder glm::vec3 first.
			glm::vec3 vector;
			// Positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			// Normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}

		// Now walk through each of the mesh's faces
		// (a face is a mesh its triangle) and retrieve the corresponding
		// vertex indices.
		for(GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// Retrieve all indices of the face and
			// store them in the indices vector
			for(GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// Return a mesh object created from the extracted mesh data
		return Ressources::Mesh(vertices, indices, defaultShader);
	}
}
