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
		if(!scene)
			LOG(ERROR) << "Cannot load scene named " << fn;
	}
}
