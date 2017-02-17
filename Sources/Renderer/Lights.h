/*
 * scene_light.hpp
 * Light controller main header
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <glm/glm.hpp>
#include <GL/glut.h>

namespace Renderer {
	class Lights {
		public:
			Lights();
			void toggleLight(int id);

		private:
			// UBO Id
			GLuint UBO;
	};
}
