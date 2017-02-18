/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <GL/glew.h>
#include <cmath>
#include <cstring>
#include "easylogging++.h"

#include "Lights.h"

namespace Renderer {
	Lights::Lights() {
		// Init the array
		dash_LightSourceParameters default_lightParam = {
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			1.0f,
			90.0f,
			0.0f,
			1.0f,
			0.0f,
			0.0f,
			false
		};
		for(int i=0;i<MAX_NUM_LIGHTS; i++) {
			lights[i] = default_lightParam;
		}
		// Gen the UBO
		glGenBuffers(1, &UBO);
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		glBufferData(GL_UNIFORM_BUFFER,
				sizeof(lights),
				&lights, GL_DYNAMIC_COPY);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		// Light is on Binding Index 1
		GLuint binding_point_index = 1;
		glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, UBO);

	}

	void Lights::update_UBO() {
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		std::memcpy(p, &lights,
				sizeof(lights));
		glUnmapBuffer(GL_UNIFORM_BUFFER);
		LOG(DEBUG) << "Updated Light parameters";
	}

	void Lights::set_light_state(int ID, bool state) {
		lights[ID].enabled = state;
	}

	void Lights::set_ambient(int ID, glm::vec4 ambient) {
		lights[ID].ambient = ambient;
	}

	void Lights::set_diffuse(int ID, glm::vec4 diffuse) {
		lights[ID].diffuse = diffuse;
	}

	void Lights::set_specular(int ID, glm::vec4 spec) {
		lights[ID].specular = spec;
	}

	void Lights::set_position(int ID, glm::vec4 pos) {
		lights[ID].position = pos;
	}

	void Lights::set_direction(int ID, glm::vec3 dir) {
		lights[ID].spotDirection = dir;
	}

	void Lights::set_exponent(int ID, float exp) {
		lights[ID].spotExponent = exp;
	}

	void Lights::set_cutoff(int ID, float cutoff) {
		// Clamp value if under 0 or above 90
		cutoff = std::max(0.0f, std::min(cutoff, 90.0f));
		lights[ID].spotCutoff = cutoff;
		lights[ID].spotCosCutoff = std::cos(cutoff * M_PI/180);
	}

	void Lights::set_attenuation(int ID, float K0, float K1, float K2) {
		lights[ID].constantAttenuation = K0;
		lights[ID].linearAttenuation = K1;
		lights[ID].quadraticAttenuation = K2;
	}
}
