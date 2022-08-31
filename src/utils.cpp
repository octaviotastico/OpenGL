// Local imports
#include "utils.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera* camera) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

  // Camera movement
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) (*camera).moveForward();
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) (*camera).moveBackward();
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) (*camera).moveLeft();
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) (*camera).moveRight();

  // Move up and down
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) (*camera).moveUp();
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) (*camera).moveDown();
}

std::string readShaderFile(const char* filename) {
  std::ifstream file(filename);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

template <typename T, typename U>
constexpr size_t offsetOf(U T::*member) {
  return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}