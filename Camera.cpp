#include "Camera.h"

using namespace SouthwestEngine;

Camera::Camera(int mode) {
	__viewMat = glm::mat4(1.0f);
	if (mode) {
		__projMat = glm::perspective(glm::radians(39.91f), 16.0f / 9.0f, 0.01f, 100.0f);
	}
	else {
		__projMat = glm::ortho(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

glm::mat4 Camera::GetProjectionMatrix() {
	return __projMat;
}

glm::mat4 Camera::GetViewMatrix() {
	return __viewMat;
}