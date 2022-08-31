#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

// Standard Libraries
#include <iostream>
#include <string>

// Libraries imports
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

// Local imports
#include "constants.hpp"

class Camera {
 public:
  // Camera Vectors
  glm::vec3 position;  // Position of the camera
  glm::vec3 z;         // Direction the camera is pointing at
  glm::vec3 y;         // Up vector of the camera
  glm::vec3 x;         // Right vector of the camera

  // Camera attributes
  bool is_perspective;  // Whether the camera is in perspective or orthographic mode
  float aspectRatio;    // Aspect ratio of the camera
  float nearPlane;      // Near plane of the camera
  float farPlane;       // Far plane of the camera
  float fov;            // Field of view of the camera

  // Euler Angles
  float yaw;    // Horizontal rotation of the camera
  float pitch;  // Vertical rotation of the camera

  // User configs
  float speed;        // Speed of the camera
  float sensitivity;  // Sensitivity of the camera

  // Matrices
  glm::mat4 projection;
  glm::mat4 cameraView;

  Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 5.0f),        //
         glm::vec3 camZ = glm::vec3(0.0f, 0.0f, -1.0f),      //
         glm::vec3 camY = glm::vec3(0.0f, 1.0f, 0.0f),       //
         glm::vec3 camX = glm::vec3(1.0f, 0.0f, 0.0f),       //
         bool _is_perspective = true,                        //
         float _aspectRatio = (float)WIDTH / (float)HEIGHT,  //
         float _nearPlane = 0.1f,                            //
         float _farPlane = 100.0f,                           //
         float _fov = 45.0f,                                 //
         float _yaw = -90.0f,                                //
         float _pitch = 0.0f,                                //
         float _speed = 0.05f,                               //
         float _sensitivity = 0.1f                           //
  );

  void moveForward(float deltaTime = 1.0f);
  void moveBackward(float deltaTime = 1.0f);
  void moveLeft(float deltaTime = 1.0f);
  void moveRight(float deltaTime = 1.0f);
  void moveUp(float deltaTime = 1.0f);
  void moveDown(float deltaTime = 1.0f);

  void activatePolygonMode();
  void deactivatePolygonMode();
};

#endif  // __CAMERA_HPP__