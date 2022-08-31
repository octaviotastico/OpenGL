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

  // Create a Vertex Array Object
  VertexArray VAO;

  // Create a Vertex Buffer Object
  VertexBuffer VBO(modelVertices, sizeof(modelVertices));

  // Create a Vertex Buffer Layout (how to read the VBO)
  VertexBufferLayout layout(sizeof(Vertex));
  layout.push(4, GL_FLOAT, offsetof(Vertex, position));       // Position
  layout.push(4, GL_FLOAT, offsetof(Vertex, color));          // Color
  layout.push(2, GL_FLOAT, offsetof(Vertex, textureCoords));  // Texture Coords

  VAO.addVertexBufferObject(VBO, layout);

  // Create an Element Buffer Object (index buffer)
  IndexBuffer IBO(modelIndices, sizeof(modelIndices));

  // Generate a program with the vertex and the fragment shader
  Shader shaderProgram;

  // Check if the program was successfully created
  if (shaderProgram.error) {  // TODO: Add error checking to vao and vbo too
    std::cout << "Failed to generate shader program" << std::endl;
    return EXIT_FAILURE;
  }

  // Loading the textures
  Texture cubeTexture("rsc/textures/cube.jpg");
  cubeTexture.bind();
  shaderProgram.updateUniform("uTexture", cubeTexture.getTextureIndex());

  // Enable depth (enables the Z-buffer)
  glEnable(GL_DEPTH_TEST);

  shaderProgram.updateUniform("uProjection", camera.projection);

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Calculate deltatime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Process input
    processInput(window, &camera);

    // Clear the screen
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update the cube position
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * 100), glm::vec3(0.25f, 1.0f, 0.0f));
    shaderProgram.updateUniform("uModel", model);

    // Update the camera position
    shaderProgram.updateUniform("uCameraView", camera.cameraView);

    // Draw the cube
    glDrawElements(GL_TRIANGLES, modelIndicesCount, GL_UNSIGNED_INT, 0);

    // Swap the buffers
    glfwSwapBuffers(window);

    // Poll for events
    glfwPollEvents();
  }

  // Clear all resources allocated by GLFW.
  shaderProgram.free();
  glfwTerminate();

  return EXIT_SUCCESS;
}
