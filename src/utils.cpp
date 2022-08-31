// Local imports
#include "utils.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, glm::vec3* cameraPos, glm::vec3* cameraX, glm::vec3* cameraY,
                  glm::vec3* cameraZ) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

  // Camera movement
  const float cameraSpeed = 0.05f;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) (*cameraPos) += (*cameraZ) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) (*cameraPos) -= (*cameraZ) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) (*cameraPos) -= (*cameraX) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) (*cameraPos) += (*cameraX) * cameraSpeed;

  // Move up and down
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) (*cameraPos) += glm::vec3(0.0f, 0.05f, 0.0f);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    (*cameraPos) -= glm::vec3(0.0f, 0.05f, 0.0f);
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