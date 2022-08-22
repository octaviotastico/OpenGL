// Local imports
#include "utils.hpp"

// Makes sure the viewport matches the new window dimensions; note that width
// and height will be significantly larger than specified on retina displays.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
