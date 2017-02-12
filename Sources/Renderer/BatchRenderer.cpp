/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <memory>
#include "easylogging++.h"

#include "Ressources/Config.h"

#include "Renderer/BatchRenderer.h"

namespace Renderer {
	void Batch::init(std::shared_ptr<Ressources::Config> lConfigManager) {
		// Set config manager
		this->lConfigManager = lConfigManager;
	}

	void Batch::set_scene(const aiScene* scene) {
		this->scene = scene;
	}

	void Batch::render() {
		if(!scene->HasCameras()) {
			LOG(ERROR) << "Fatal error: scene has not any camera to render!";
			return;
		}

		// Start rendering each camera
		for(int i=0; i< scene->mNumCameras; i++) {
			
		}
	}
}
