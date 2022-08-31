// Libraries imports
#include <GLAD/glad.h>   // GLAD: https://github.com/Dav1dde/glad
#include <GLFW/glfw3.h>  // GLFW: https://es.wikipedia.org/wiki/GLFW

#include <GLM/glm.hpp>  // GLM: https://github.com/g-truc/glm
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

// Standard Libraries
#include <iostream>

// Local imports
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
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraZ = glm::vec3(0.0f, 0.0f, -1.0f);  // Direction of the camera
glm::vec3 cameraY = glm::vec3(0.0f, 1.0f, 0.0f);   // Up vector of the camera
glm::vec3 cameraX = glm::cross(cameraZ, cameraY);  // Right vector of the camera
float fov = 45.0f;

// Euler angles
float yaw = -90.0f;
float pitch = 0.0f;

// Mouse variables
double lastX = WIDTH / 2.0;
double lastY = HEIGHT / 2.0;

// Todo: Clean this up, and send everything to processInput()
void mouseCallback(GLFWwindow* window, double newX, double newY) {
  float xpos = (float)newX;
  float ypos = (float)newY;

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;  // Reversed
  lastX = xpos;
  lastY = ypos;

  float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraZ = glm::normalize(front);
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
  if (shaderProgram.error) {
    std::cout << "Failed to generate shader program" << std::endl;
    return EXIT_FAILURE;
  }

  // Loading the textures
  int cubeTexture = 0;
  Texture texture("rsc/textures/cube.jpg");
  texture.bind(cubeTexture);
  shaderProgram.updateUniform("uTexture", cubeTexture);

  // Testing stuff
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Enable depth (enables the Z-buffer)
  glEnable(GL_DEPTH_TEST);

  // Create transformations matrices
  glm::mat4 projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
  shaderProgram.updateUniform("uProjection", projection);

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Check for the user input
    processInput(window, &cameraPos, &cameraX, &cameraY, &cameraZ);

    // Color for clearing the screen
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    // Clears the screen and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * 100), glm::vec3(0.25f, 1.0f, 0.0f));
    shaderProgram.updateUniform("uModel", model);

    // camera/view transformation
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraZ, cameraY);
    shaderProgram.updateUniform("uCameraView", view);

    // Draw the triangle
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
