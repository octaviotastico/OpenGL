// Standard Libraries
#include <iostream>

// Libraries imports
#include <GLAD/glad.h>   // GLAD: https://github.com/Dav1dde/glad
#include <GLFW/glfw3.h>  // GLFW: https://es.wikipedia.org/wiki/GLFW

#include <GLM/glm.hpp>  // GLM: https://github.com/g-truc/glm
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

// Local imports
#include "src/camera.hpp"
#include "src/constants.hpp"
#include "src/errors.hpp"
#include "src/indexBuffer.hpp"
#include "src/lights.hpp"
#include "src/model.hpp"
#include "src/shaders.hpp"
#include "src/textures.hpp"
#include "src/utils.hpp"
#include "src/vertex.hpp"
#include "src/vertexArray.hpp"
#include "src/vertexBuffer.hpp"
#include "src/vertexBufferLayout.hpp"

// Models
#include "rsc/models/mCube.hpp"

// Camera
Camera camera;

// Mouse variables
bool firstMouse = true;
double lastX = WIDTH / 2.0;
double lastY = HEIGHT / 2.0;

// Time variables
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;

void mouseCallback(GLFWwindow* window, double newX, double newY) {
  float xPos = (float)newX;
  float yPos = (float)newY;

  if (firstMouse) {
    lastX = xPos;
    lastY = yPos;
    firstMouse = false;
  }

  float xOffset = xPos - lastX;
  float yOffset = lastY - yPos;  // Reversed

  lastX = xPos;
  lastY = yPos;

  camera.mouseMovement(xOffset, yOffset);
}

int main() {
  // Create the window
  GLFWwindow* window = NULL;

  // Init GLFW
  glfwInit();

  // Configure GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create a GLFWwindow
  window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

  // Check if the window was succesfully created
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }

  // Make the context current
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSwapInterval(1);  // Enable vsync

  // Configure input
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Initialize GLAD (load all OpenGL function pointers)
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return EXIT_FAILURE;
  }

  // Generate a program with the vertex and the fragment shader
  Shader shaderProgram("rsc/shaders/basic.vertex.glsl", "rsc/shaders/basic.fragment.glsl");

  // Check if the program was successfully created
  if (shaderProgram.error) {
    std::cout << "Failed to generate shader program" << std::endl;
    return EXIT_FAILURE;
  }

  // MODEL
  Model planet("rsc/models/planet/planet.obj");
  glCheckError();

  // Enable depth (enables the Z-buffer)
  glEnable(GL_DEPTH_TEST);
  glCheckError();

  // Draw in wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    glCheckError();

    // Calculate deltatime
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Process input
    processInput(window, &camera);
    glCheckError();

    // Clear the screen
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCheckError();

    // Update the cube position
    glm::mat4 model = glm::mat4(1.0f);

    // translate it down so it's at the center of the scene
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    // it's a bit too big for our scene, so scale it down
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    // Update the shaders
    shaderProgram.bind();
    shaderProgram.updateUniform("uProjection", camera.projection);
    shaderProgram.updateUniform("uCameraView", camera.cameraView);
    shaderProgram.updateUniform("uModel", model);
    glCheckError();

    planet.Draw(shaderProgram);
    glCheckError();

    // Swap the buffers
    glfwSwapBuffers(window);
    glCheckError();

    // Poll for events
    glfwPollEvents();
    glCheckError();
  }

  // Clear all resources allocated by GLFW.
  shaderProgram.free();
  // lightsProgram.free();
  glfwTerminate();

  return EXIT_SUCCESS;
}
