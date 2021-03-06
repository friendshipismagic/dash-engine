/*
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

#define MAX_NUM_LIGHTS 8

namespace Renderer {
	class Lights {
		public:
			Lights();

			/// Change light parameters
			// Enable or disable light
			void set_light_state(int, bool);
			// Change ambient value
			void set_ambient(int, glm::vec4);
			// Change diffuse value
			void set_diffuse(int, glm::vec4);
			// Change specular value
			void set_specular(int, glm::vec4);
			// Change position
			void set_position(int, glm::vec4);
			// Change direction (only if directive spot)
			void set_direction(int, glm::vec3);
			// Change exponent
			void set_exponent(int, float);
			// Change cut-off value
			void set_cutoff(int, float);
			// Change Attenuation values, constant, linear then quadratic
			void set_attenuation(int ID, float K0, float K1, float K2);

			// Update Lights
			void update_UBO();

		private:

			// Default structure of the UBO
			// This structure is the same as defined in OpenGL Shader
			// Language Specifications in V 1.30 and newer
			// XXX: Warning UBO Alignment is based of std140 norm
			// Padding is necessary to correctly fill the structure
			// See: http://sunandblackcat.com/tipFullView.php?l=eng&topicid=21
			// &topic=OpenGL-Uniform-Buffer-Objects for detailled explanation
			// of how to do this.
			struct dash_LightSourceParameters {
				glm::vec4 ambient; // Acli
				glm::vec4 diffuse; // Dcli
				glm::vec4 specular; // Scli
				glm::vec4 position; // Ppli
				glm::vec3 spotDirection; // Sdli
				GLfloat spotExponent; // Srli
				GLfloat spotCutoff; // Crli, range: [0.0,90.0], 180.0
				GLfloat spotCosCutoff; // cos(Crli), range: [1.0,0.0] -1.0
				GLfloat constantAttenuation; // K0
				GLfloat linearAttenuation; // K1
				GLfloat quadraticAttenuation;// K2
				GLint enabled;
				GLfloat __padding_NOUSE[2]; // See above for more details
			};

			dash_LightSourceParameters lights[MAX_NUM_LIGHTS];

			// UBO Id
			GLuint UBO;
	};
}
