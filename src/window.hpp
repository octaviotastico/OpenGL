#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

// Standard imports
#include <stdlib.h>

#include <iostream>

// Libraries imports
#include "../dependencies/include/GLFW/glfw3.h"

// Local imports
#include "constants.hpp"
#include "utils.hpp"

// Initializes GLFW and configures it.
void initAndConfigGLFW();

// Creates a GLFW window.
void createGLFWwindow(GLFWwindow** window);

#endif  // __WINDOW_HPP__