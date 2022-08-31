#include "camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 camZ, glm::vec3 camY, glm::vec3 camX, bool _is_perspective,
               float _aspectRatio, float _nearPlane, float _farPlane, float _fov, float _yaw,
               float _pitch, float _speed, float _sensitivity) {
  // Initialize camera vectors
  position = glm::vec3(pos[0], pos[1], pos[2]);
  z = glm::vec3(camZ[0], camZ[1], camZ[2]);
  y = glm::vec3(camY[0], camY[1], camY[2]);
  x = glm::vec3(camX[0], camX[1], camX[2]);

  // Initialize camera attributes
  is_perspective = _is_perspective;
  aspectRatio = _aspectRatio;
  nearPlane = _nearPlane;
  farPlane = _farPlane;
  fov = _fov;

  // Initialize Euler angles
  yaw = _yaw;
  pitch = _pitch;

  // Initialize user configs
  speed = _speed;
  sensitivity = _sensitivity;

  // Initialize projection matrix
  if (is_perspective) {
    projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
  } else {
    projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
  }

  // Initialize camera view matrix
  cameraView = glm::lookAt(position, position + z, y);
}

void Camera::moveForward(float deltaTime) {
  position += z * speed * deltaTime;
  cameraView = glm::lookAt(position, position + z, y);
}

void Camera::moveBackward(float deltaTime) {
  position -= z * speed * deltaTime;
  cameraView = glm::lookAt(position, position + z, y);
}

void Camera::moveLeft(float deltaTime) {
  position -= x * speed * deltaTime;
  cameraView = glm::lookAt(position, position + z, y);
}

void Camera::moveRight(float deltaTime) {
  position += x * speed * deltaTime;
  cameraView = glm::lookAt(position, position + z, y);
}

void Camera::moveUp(float deltaTime) {
  position += y * speed * deltaTime;
  cameraView = glm::lookAt(position, position + z, y);
}

void Camera::moveDown(float deltaTime) {
  position -= y * speed * deltaTime;
  cameraView = glm::lookAt(position, position + z, y);
}

void Camera::mouseMovement(float xOffset, float yOffset) {
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  yaw += xOffset;
  pitch += yOffset;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  glm::vec3 newZ;
  newZ.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  newZ.y = sin(glm::radians(pitch));
  newZ.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  z = glm::normalize(newZ);

  x = glm::normalize(glm::cross(z, glm::vec3(0.0f, 1.0f, 0.0f)));
  y = glm::normalize(glm::cross(x, z));

  cameraView = glm::lookAt(position, position + z, y);
}

void Camera::activatePolygonMode() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

void Camera::deactivatePolygonMode() { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }