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

#include "Ressources/Models.h"
#include "Ressources/Config.h"

namespace Renderer {
	class Batch {
		public:
			// Default constructor, should not do anything
			Batch() {};
			// Default destructor, should not do anything
			~Batch() {};

			// Initalizer, retrieves the rendering configuration from config
			// manager
			void init(std::shared_ptr<Ressources::Config>);

			// Add a scene to render
			// XXX: Why do I need these awful raw pointers...
			void set_scene(const aiScene*);

			// Start a rendering process now, using current opengl context
			void render();
		private:
			// Config manager
			std::shared_ptr<Ressources::Config> lConfigManager;

			// List of scenes to render
			const aiScene* scene;
	};
}
