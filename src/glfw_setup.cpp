#include "glfw_setup.hpp"

GLFWwindow* glfw_setup_window(int major_version, int minor_version, int width, int height,
                              const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
  // Create the window
  GLFWwindow* window = nullptr;

  // Init GLFW
  glfwInit();

  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // For Mac compatibility
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a GLFWwindow object that we can use for GLFW's functions
  window = glfwCreateWindow(width, height, title, monitor, share);

  // This is just made for compatibility
  int screenWidth, screenHeight;
  glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

  // Check if the window was succesfully created
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();

    return nullptr;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return nullptr;
  }

  // Define the viewport dimensions
  glViewport(0, 0, screenWidth, screenHeight);

  return window;
}