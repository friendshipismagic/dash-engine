/*
 * scene_light.cpp
 * File describing the light controller
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include "Lights.h"

#include <GL/glut.h>
#include <iostream>

#include "easylogging++.h"

namespace Renderer {
	Lights::Lights() {
		// Load every light parameters in GPU
		for(int i = 0; i < 8; i++) {
			glLightfv(gl_lights[i], GL_POSITION, light_position[i]);
			glLightfv(gl_lights[i], GL_DIFFUSE, color[i]);
			glLightfv(gl_lights[i], GL_SPECULAR, color[i]);
		}
	}

	void Lights::toggleLight(int id) {
		if(glIsEnabled(gl_lights[id]) == GL_TRUE) {
			glDisable(gl_lights[id]);
			LOG(DEBUG) << "Disabling light " << id;
		} else {
			glEnable(gl_lights[id]);
			LOG(DEBUG) << "Enabling light " << id;
		}
	}

	void Lights::setLightPosition(int id, glm::vec4 pos) {
		light_position[id][0] = pos.x;
		light_position[id][1] = pos.y;
		light_position[id][2] = pos.z;
		light_position[id][3] = pos.w;
	}

	glm::vec4 Lights::getLightPosition(int id) {
		glm::vec4 vector(light_position[id][0],
				light_position[id][1],
				light_position[id][2],
				light_position[id][3]);
		return vector;
	}

	void Lights::setLightColor(int id, glm::vec4 colorvec) {
		color[id][0] = colorvec.x;
		color[id][1] = colorvec.y;
		color[id][2] = colorvec.z;
		color[id][3] = colorvec.w;
	}

	glm::vec4 Lights::getLightColor(int id) {
		glm::vec4 vector(color[id][0],
				color[id][1],
				color[id][2],
				color[id][3]);
		return vector;
	}
}
