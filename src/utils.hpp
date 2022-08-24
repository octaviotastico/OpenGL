// Standard Libraries
#include <fstream>
#include <iostream>
#include <sstream>

// Libraries imports
#include <GLFW/glfw3.h>

// GLFW: Whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Reads all input from the keyboard and mouse, and handles the input events.
void processInput(GLFWwindow* window);

// Reads the contents of a file and returns it as a string.
std::string readShaderFile(const char* filename);
