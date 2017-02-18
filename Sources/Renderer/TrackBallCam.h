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
			// Change camera position
			void set_position(glm::vec3);
			// Change focal lens
			void set_focal_lens(float);
			// Change Depth Of View
			void set_dof_distance(float);
			// Change clipping
			void set_clipping(float, float);

			// Relative movements
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

		pivate:
			// Position, in polar coordinates
			struct camera_UBO {
				glm::vec3 position;
				glm::vec3 direction;
				glm::vec3 right;
				glm::vec3 up;
				GLfloat focal_lens;
				GLfloat dof_dist;
				GLfloat clip_start;
				GLfloat clip_end;
			};
	};
}
