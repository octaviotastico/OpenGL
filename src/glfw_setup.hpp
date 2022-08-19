// Libraries imports
#include <GL/glew.h>     // GLEW: https://es.wikipedia.org/wiki/GLEW
#include <GLFW/glfw3.h>  // GLFW: https://es.wikipedia.org/wiki/GLFW

#define GLEW_STATIC

// Standard Libraries
#include <iostream>

// Local imports
#include "constants.hpp"

// Namespaces used
using namespace std;

/**
 * This function creates and returns a GLFW window with the given parameters.
 *
 * @param major_version: The context client API major version to be used in glfwWindowHint.
 * @param minor_version: The context client API minor version to be used in glfwWindowHint.
 * @param width: The initial width of the window to be created.
 * @param height: The initial height of the window to be created.
 * @param title: The title that will be shown in the window.
 * @param monitor: The monitor to use for full screen mode (null will be windowed mode).
 * @param window: The window whose context to share resources with (null will be not to share).
 */
GLFWwindow* glfw_setup_window(int major_version = MAJOR_VERSION, int minor_version = MINOR_VERSION,
                              int width = WIDTH, int height = HEIGHT, const char* title = TITLE,
                              GLFWmonitor* monitor = MONITOR, GLFWwindow* share = SHARE);
