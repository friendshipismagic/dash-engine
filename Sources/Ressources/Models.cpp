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
		this->filepath = fm->getModelsFolderPath() + fn;

		// Taken from the usage doc
		importer = std::make_shared<Assimp::Importer>();

		// Read the file and do some postprocessing on it, the postprocessing
		// should be configured in the config: TODO
		scene = importer->ReadFile(filepath,
				aiProcess_CalcTangentSpace      |
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
		std::vector<Ressources::Texture> textures;

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
			// Texture Coordinates
			// Does the mesh contain texture coordinates?
			if(mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				// A vertex can contain up to 8 different texture coordinates.
				// We thus make the assumption that we won't use models where a
				// vertex can have multiple texture coordinates so we always
				// take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x; 
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
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

		// Process materials
		if(mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// We assume a convention for sampler names in the shaders.
			// Each diffuse texture should be named as 'texture_diffuseN'
			// where N is a sequential number ranging
			// from 1 to MAX_SAMPLER_NUMBER. 
			// Same applies to other texture as the following list summarizes:
			// Diffuse: texture_diffuseN
			// Specular: texture_specularN
			// Normal: texture_normalN

			// 1. Diffuse maps
			std::vector<Texture> diffuseMaps =
				this->loadMaterialTextures(material, aiTextureType_DIFFUSE,
						"texture_diffuse");
			textures.insert(textures.end(),
					diffuseMaps.begin(), diffuseMaps.end());

			// 2. Specular maps
			std::vector<Texture> specularMaps =
				this->loadMaterialTextures(material, aiTextureType_SPECULAR,
						"texture_specular");
			textures.insert(textures.end(),
					specularMaps.begin(), specularMaps.end());
		}

		// Return a mesh object created from the extracted mesh data
		// TODO Add default Shader
		return Ressources::Mesh(vertices, indices, textures);
	}

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
			aiTextureType type, std::string typeName) {
		std::vector<Texture> textures;
		for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
		}
		return textures;
	}  

}
