#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "sw.h"

#define CAMERA_MODE_ORTHOGRAPHIC 0
#define CAMERA_MODE_PERSPECTIVE 1

namespace SouthwestEngine {
	class Camera {
	private:
		glm::mat4 __viewMat;
		glm::mat4 __projMat;
	public:
		Camera(int mode);
		// Get the view matrix for this camera
		glm::mat4 GetViewMatrix();
		// Get the projection matrix for this camera
		glm::mat4 GetProjectionMatrix();
	};
}

#endif