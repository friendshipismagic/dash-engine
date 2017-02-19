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

namespace Renderer {
	class TrackBallCam {
		public:
			TrackBallCam();

			/// Change camera parameters
			// Change aspect ratio
			void set_aspect_ratio(float);
			// Change Fov, in degrees
			void set_field_of_view(float);
			// Change Depth Of View
			void set_dof_distance(float);
			// Change clipping
			void set_clipping(float, float);

			/// Relative movements
			// Change distance to center (zoom, dezoom)
			void zoom(float);
			// Rotate camera (theta, phi), radians
			void rotate(glm::vec2);
			// Pan (x, y, z)
			void pan(glm::vec3);
			// without moving camera's position
			// Yaw in radians
			void yaw(float);
			// Pitch in radians
			void pitch(float);
			// Roll in radians
			void roll(float);

			/// Get V+P matrices
			// Get View matrix
			glm::mat4 get_V();
			// Get Projection matrix
			glm::mat4 get_P();

		private:
			// Position, in polar coordinates (r, theta, phi), radians
			glm::vec3 position = glm::vec3(5.0f, 0.0f, 0.0f);
			// Other parameters used to set camera, in cartesian coordinates
			glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
			float field_of_view = 45; // in degrees
			float clip_start = 0.1f;
			float clip_end = 10.0f;
			float aspect_ratio = 16/9;
			// Should we recalculate V or P?
			bool v_changed = true;
			bool p_changed = true;
			// V+P Matrices
			glm::mat4 view_matrix;
			glm::mat4 proj_matrix;
	};
}
