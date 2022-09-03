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
#include "src/indexBuffer.hpp"
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

  // SHADERS
  // Generate a program with the vertex and the fragment shader
  Shader shaderProgram("rsc/shaders/basic.vertex.glsl", "rsc/shaders/basic.fragment.glsl");
  Shader lightsProgram("rsc/shaders/light.vertex.glsl", "rsc/shaders/light.fragment.glsl");

  // Check if the program was successfully created
  if (shaderProgram.error || lightsProgram.error) {
    std::cout << "Failed to generate shader program" << std::endl;
    return EXIT_FAILURE;
  }

  // CUBE
  // Create a Vertex Array Object for the cube
  VertexArray cubeVAO;

  // Create a Vertex Buffer Object
  VertexBuffer cubeVBO(modelVertices, sizeof(modelVertices));

  // Create a Vertex Buffer Layout (how to read the VBO)
  VertexBufferLayout cubeLayout(sizeof(Vertex));
  cubeLayout.push(4, GL_FLOAT, offsetof(Vertex, position));       // Position
  cubeLayout.push(4, GL_FLOAT, offsetof(Vertex, color));          // Color
  cubeLayout.push(2, GL_FLOAT, offsetof(Vertex, textureCoords));  // Texture Coords

  // Add the layout to the cube VAO
  cubeVAO.addVertexBufferObject(cubeVBO, cubeLayout);

  // Create an index buffer object for the cube
  IndexBuffer cubeIBO(modelIndices, sizeof(modelIndices));

  // Load the textures for the cube
  Texture cubeTexture("rsc/textures/cube.jpg");
  cubeTexture.bind();
  shaderProgram.updateUniform("uTexture", cubeTexture.getTextureIndex());

  // LIGHTS
  // Create a Vertex Array Object for the light source
  VertexArray lightVAO;

  // Create a Vertex Buffer Layout (how to read the VBO)
  VertexBufferLayout lightLayout(sizeof(Vertex));
  lightLayout.push(4, GL_FLOAT, offsetof(Vertex, position));

  // Add the layout to the light VAO
  lightVAO.addVertexBufferObject(cubeVBO, lightLayout);

  // Create an index buffer object for the light source
  IndexBuffer lightIBO(modelIndices, sizeof(modelIndices));

  // Enable depth (enables the Z-buffer)
  glEnable(GL_DEPTH_TEST);

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Calculate deltatime
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Process input
    processInput(window, &camera);

    // Clear the screen
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ----- DRAW THE CUBE ----- //

    // Update the cube position
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * 100), glm::vec3(0.25f, 1.0f, 0.0f));

    // Update the shaders
    cubeTexture.bind();
    shaderProgram.bind();
    shaderProgram.updateUniform("uProjection", camera.projection);
    shaderProgram.updateUniform("uCameraView", camera.cameraView);
    shaderProgram.updateUniform("uModel", model);

    // Draw the cube
    cubeVAO.draw(modelIndicesCount);

    // ----- DRAW THE LIGHTS ----- //

    // Update the lights position
    glm::mat4 lightsModel = glm::mat4(1.0f);
    lightsModel = glm::translate(lightsModel, glm::vec3(2.0f, 1.0f, 3.0f));
    lightsModel = glm::scale(lightsModel, glm::vec3(0.25f));

    // Update the shaders
    lightsProgram.bind();
    lightsProgram.updateUniform("uProjection", camera.projection);
    lightsProgram.updateUniform("uCameraView", camera.cameraView);
    lightsProgram.updateUniform("uModel", lightsModel);

    // Draw the lights
    lightVAO.draw(modelIndicesCount);

    // ---------- //

    // Swap the buffers
    glfwSwapBuffers(window);

    // Poll for events
    glfwPollEvents();
  }

  // Clear all resources allocated by GLFW.
  shaderProgram.free();
  lightsProgram.free();
  glfwTerminate();

  return EXIT_SUCCESS;
}
