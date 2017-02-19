/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

// Use radians in glm
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

#include "Renderer/TrackBallCam.h"

namespace Renderer {
	void TrackBallCam::set_aspect_ratio(float aspect_ratio) {
		this->aspect_ratio = aspect_ratio;
		// Changes Projection matrix
		p_changed = true;
	}

	void TrackBallCam::set_field_of_view(float fov) {
		this->field_of_view = fov;
		// Changes Projection matrix
		p_changed = true;
	}

	void TrackBallCam::set_clipping(float clip_start, float clip_end) {
		this->clip_start = clip_start;
		this->clip_end = clip_end;
		// Changes Projection matrix
		p_changed = true;
	}

	void TrackBallCam::zoom(float delta_radius) {
		position.x -= delta_radius;
		// Clamp value at 0
		position.x = std::max(0.0f, position.x);
		// Changes View matrix
		v_changed = true;
	}

	void TrackBallCam::rotate(glm::vec2 delta) {
		position += glm::vec3(0.0f, delta);
		// Changes View matrix
		v_changed = true;
	}

	void TrackBallCam::pan(glm::vec3 trans) {
		center += trans;
		// Changes View matrix
		v_changed = true;
	}

	void TrackBallCam::yaw(float yw) {
		// TODO
		// Changes View matrix
		v_changed = true;
	}

	void TrackBallCam::pitch(float ph) {
		// TODO
		// Changes View matrix
		v_changed = true;
	}

	void TrackBallCam::roll(float rl) {
		// TODO
		// Changes View matrix
		v_changed = true;
	}

	glm::mat4 TrackBallCam::get_V() {
		if(!v_changed) return view_matrix;
		// Rebuild view matrix otherwize
		v_changed = false;
		// The cartesian position is the cartesian coordinates of position,
		// then translated to the camera center view.
		float r = position.x;
		float theta = position.y;
		float phi = position.z;
		glm::vec3 pos_cartesian = center;
		pos_cartesian.x += r * std::sin(theta) * std::cos(phi);
		pos_cartesian.y += r * std::sin(theta) * std::sin(phi);
		pos_cartesian.z += r * std::cos(theta);

		view_matrix = glm::lookAt(pos_cartesian, center, up);
		return view_matrix;
	}

	glm::mat4 TrackBallCam::get_P() {
		if(!p_changed) return proj_matrix;
		// Rebuild projection matrix otherwize
		p_changed = false;
		proj_matrix = glm::perspective(
				field_of_view,
				aspect_ratio,
				clip_start,
				clip_end);
		return proj_matrix;
	}
}
