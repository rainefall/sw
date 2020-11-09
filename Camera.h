#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "sw.h"

#define CAMERA_MODE_ORTHOGRAPHIC 0
#define CAMERA_MODE_PERSPECTIVE 1

namespace SouthwestEngine {
	class Camera {
	private:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;

		float pitch, yaw, roll, fov, near, far;

		glm::mat4 __projMat;
	public:
		Camera(int mode);

		// Get the view matrix for this camera
		glm::mat4 GetViewMatrix();
		// Get the projection matrix for this camera
		glm::mat4 GetProjectionMatrix();

		// Move the camera
		void Translate(float x, float y, float z);
		// Rotate the camera (euler angles)
		void Rotate(float x, float y, float z);
		// Set position
		void SetPosition(float x, float y, float z);
		// Set X position
		void SetX(float x);
		// Set Z position
		void SetY(float y);
		// Set Z position
		void SetZ(float z);

		// Recreate projection matrix
		void SetProjectionMatrix(float f, float n, float fr);
		// Look at
		void LookAt(glm::vec3 target);
	};
}

#endif