#include "Camera.h"

using namespace SouthwestEngine;

Camera::Camera(int mode) {
	position = glm::vec3(0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	pitch = 0;
	roll = 0;
	yaw = 0;
	fov = 80.0f;
	near = 0.1f;
	far = 100.0f;

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
	glm::mat4 m = glm::rotate(glm::mat4(1.0f), glm::radians(-pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	m = glm::rotate(m, glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	m = glm::rotate(m, glm::radians(-roll), glm::vec3(0.0f, 0.0f, 1.0f));
	m = glm::translate(m, -position);
	return m;
}

// Move the camera
void Camera::Translate(float x, float y, float z) {
	position += glm::vec3(x, y, z);
}

void Camera::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::SetX(float x) {
	position.x = x;
}

void Camera::SetY(float y) {
	position.y = y;
}

void Camera::SetZ(float z) {
	position.z = z;
}

void Camera::SetProjectionMatrix(float f, float n, float fr)
{
	fov = f;
	near = n;
	far = fr;
	// setup projection
	__projMat = glm::perspective(glm::radians(f), 16.0f/9.0f, n, f);
}

void Camera::LookAt(glm::vec3 target) {
	front = target - position;
}

// Rotate the camera (euler angles)
void Camera::Rotate(float p, float y, float r) {
	pitch += p;
	yaw += y;
	roll += r;

	glm::vec3 direction;
	direction.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = cos(glm::radians(-yaw)) * sin(glm::radians(pitch));
	front = glm::normalize(direction);
}
