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

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "Ressources/Mesh.h"

#include "Ressources/Ressources.h"

namespace Ressources {
	class Models {
		public:
			// Initializer, taking a model filename and ressource manager to get
			// the Models folder
			void init(std::shared_ptr<Ressources::Manager> fm, std::string fn);

			// Get the scene object (everything is seen as a scene)
			const aiScene* get_scene() const { return scene; };

			// Render the whole scene
			void render_scene();

		private:
			// Private import recursive calls
			void processNode(aiNode* node, const aiScene* scene);
			Ressources::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
			std::vector<Texture> loadMaterialTextures(aiMaterial*,
					aiTextureType, std::string);

			std::string filepath;
			// Importer is the importer class, that fully manages the scene
			// pointer, making a smart pointer useless for scene object...
			std::shared_ptr<Assimp::Importer> importer;
			const aiScene* scene;
			// List of meshes the scene contains
			std::vector<Ressources::Mesh> meshes;
	};
}
