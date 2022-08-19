// Local includes
#include "src/glfw_setup.hpp"

int main() {
  // Create a window
  GLFWwindow* window = glfw_setup_window();

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    continue;
  }

  // Terminate GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();

  return EXIT_SUCCESS;
}
