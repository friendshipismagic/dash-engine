/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include "Lights.h"

#include <cmath>
#include <cstring>
#include "easylogging++.h"

namespace Renderer {
	Lights::Lights() {
		// Gen the UBO
		glGenBuffers(1, &UBO);
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		glBufferData(GL_UNIFORM_BUFFER,
				lights.size() * sizeof(gl_LightSourceParameters),
				&lights[0], GL_DYNAMIC_COPY);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void Lights::update_UBO() {
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		std::memcpy(p, &lights[0],
				lights.size() * sizeof(gl_LightSourceParameters));
		glUnmapBuffer(GL_UNIFORM_BUFFER);
		LOG(DEBUG) << "Updated Light parameters";
	}

	void Lights::add_light() {
		gl_LightSourceParameters light_params;
		lights.push_back(light_params);
		// Return lastID and increment it after
		return lastID++;
	}

	void Light::set_light_state(int ID, bool state) {
		lights[ID].enabled = state;
	}

	void Light::set_ambient(int ID, glm::vec4 ambient) {
		lights[ID].ambient = ambient;
	}

	void Light::set_diffuse(int ID, glm::vec4 diffuse) {
		lights[ID].diffuse = diffuse;
	}

	void Light::set_specular(int ID, glm::vec4 spec) {
		lights[ID].specular = spec;
	}

	void Light::set_position(int ID, glm::vec4 pos) {
		lights[ID].position = pos;
	}

	void Light::set_direction(int ID, glm::vec3 dir) {
		lights[ID].spotDirection = dir;
	}

	void Light::set_exponent(int ID, float exp) {
		lights[ID].spotExponent = exp;
	}

	void Light::set_cutoff(int ID, float cutoff) {
		// Clamp value if under 0 or above 90
		cutoff = std::max(0.0f, std::min(cutoff, 90.0f);
		lights[ID].spotCutoff = cutoff;
		lights[ID].spotCosCutoff = std::cos(cutoff * std::PI/180);
	}

	void Light::set_attenuation(int ID, float K0, float K1, float K2) {
		lights[ID].constantAttenuation = K0;
		lights[ID].linearAttenuation = K1;
		lights[ID].quadraticAttenuation = K2;
	}
}
