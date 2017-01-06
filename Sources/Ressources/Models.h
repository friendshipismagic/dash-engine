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

#include "Ressources/Ressources.h"

namespace Ressources {
	class Models {
		public:
			// Default constructor, should not do anything
			Models() {};
			// Default destructor, should not do anything
			~Models() {};

			// Initializer, taking a model filename and ressource manager to get
			// the Models folder
			void init(std::shared_ptr<Ressources::Manager> fm, std::string fn);

			// Get the scene object (everything is seen as a scene)
			std::shared_ptr<const aiScene> getScene() { return scene; };

		private:
			std::string filepath;
			std::shared_ptr<const aiScene> scene;

	};
}
