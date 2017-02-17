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
#include <vector>

namespace Renderer {
	class Lights {
		public:
			Lights();
			void toggleLight(int id);

		private:
			void update_UBO();

			// Default structure of the UBO
			// This structure is the same as defined in OpenGL Shader
			// Language Specifications in V 1.30 and newer
			struct gl_LightSourceParameters {
				glm::vec4 ambient; // Acli
				glm::vec4 diffuse; // Dcli
				glm::vec4 specular; // Scli
				glm::vec4 position; // Ppli
				glm::vec4 halfVector; // Derived: Hi
				glm::vec3 spotDirection; // Sdli
				float spotExponent; // Srli
				float spotCutoff; // Crli
				// (range: [0.0,90.0], 180.0)
				float spotCosCutoff; // Derived: cos(Crli)
				// (range: [1.0,0.0],-1.0)
				float constantAttenuation; // K0
				float linearAttenuation; // K1
				float quadraticAttenuation;// K2
			};

			std::vector<gl_LightSourceParameters> lights;

			// UBO Id
			GLuint UBO;
	};
}
