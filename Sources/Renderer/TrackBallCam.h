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

namespace Renderer {
	class TrackBallCam {
		public:
			TrackBallCam();

			/// Change camera parameters
			// Change aspect ratio
			void set_aspect_ratio(float);
			// Change focal lens
			void set_focal_lens(float);
			// Change Depth Of View
			void set_dof_distance(float);
			// Change clipping
			void set_clipping(float, float);

			/// Relative movements
			// Change distance to center (zoom, dezoom)
			void zoom(float);
			// Rotate camera
			void rotate(glm::vec2);
			// Pan
			void pan(glm::vec2);
			// without moving camera's position
			// Yaw
			void yaw(float);
			// Pitch
			void pitch(float);
			// Roll
			void roll(float);

			/// Get V+P matrices
			// Get View matrix
			glm::mat4 get_V();
			// Get Projection matrix
			glm::mat4 get_P();

		pivate:
			// Position, in polar coordinates (r, theta, phi)
			glm::vec3 position;
			// Other parameters used to set camera, in cartesian coordinates
			glm::vec3 direction;
			glm::vec3 right;
			glm::vec3 up;
			float focal_lens;
			float dof_dist;
			float clip_start;
			float clip_end;
			float aspect_ratio;
			// Should we recalculate V or P ?
			bool v_changed;
			bool p_changed;
			// V+P Matrices
			glm::mat4 view_matrix;
			glm::mat4 proj_matrix;
	};
}
