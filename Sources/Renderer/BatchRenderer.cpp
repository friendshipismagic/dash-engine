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
	void Batch::init(std::shared_ptr<Ressources::Config> lConfigManager,
			std::shared_ptr<GameWindows::Manager> lWindowManager) {
		// Set config manager
		this->lConfigManager = lConfigManager;
		// Set window manager
		this->lWindowManager = lWindowManager;
	}

	void Batch::set_scene(std::shared_ptr<Ressources::Models> model) {
		this->model = model;
	}

	void Batch::render() {
		// Just render the raw model for now
		model->render_scene();

		// Swap buffers
		lWindowManager->swap_buffers();
	}
}
