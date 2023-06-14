#ifndef __UTILS_HPP__
#define __UTILS_HPP__

// Standard Libraries
#include <fstream>
#include <iostream>
#include <sstream>

// Libraries imports
#include "../dependencies/include/GLFW/glfw3.h"
#include "../dependencies/include/GLM/glm.hpp"
#include "../dependencies/include/GLM/gtc/matrix_transform.hpp"
#include "../dependencies/include/GLM/gtc/type_ptr.hpp"

// Local imports
#include "camera.hpp"

// GLFW: Whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Handles mouse movement
void mouseInput(GLFWwindow* window, Camera* camera, double newX, double newY, double* lastX, double* lastY,
                bool* firstMouseMovement);

// Reads all input from the keyboard and mouse, and handles the input events.
void processInput(GLFWwindow* window, Camera* camera);

// Reads the contents of a file and returns it as a string.
std::string readShaderFile(const char* filename);

// Returns the offset of a member in a class (https://stackoverflow.com/a/20141143/9826652).
template <typename T, typename U>
constexpr size_t offsetOf(U T::*member);

#endif  // __UTILS_HPP__