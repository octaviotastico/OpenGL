#include "camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 camZ, glm::vec3 camY, glm::vec3 camX, bool _is_perspective,
               float _aspectRatio, float _nearPlane, float _farPlane, float _fov, float _yaw,
               float _pitch, float _speed, float _sensitivity) {
  // Initialize camera vectors
  position = pos;
  z = camZ;
  y = camY;
  x = camX;

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

void Camera::moveForward(float deltaTime) { position += z * speed * deltaTime; }

void Camera::moveBackward(float deltaTime) { position -= z * speed * deltaTime; }

void Camera::moveLeft(float deltaTime) { position -= x * speed * deltaTime; }

void Camera::moveRight(float deltaTime) { position += x * speed * deltaTime; }

void Camera::moveUp(float deltaTime) { position += y * speed * deltaTime; }

void Camera::moveDown(float deltaTime) { position -= y * speed * deltaTime; }

void Camera::activatePolygonMode() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

void Camera::deactivatePolygonMode() { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }