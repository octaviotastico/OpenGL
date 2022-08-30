// Libraries imports
#include <GLAD/glad.h>   // GLAD: https://github.com/Dav1dde/glad
#include <GLFW/glfw3.h>  // GLFW: https://es.wikipedia.org/wiki/GLFW

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
  glfwSwapInterval(1);  // Enable vsync

  // Initialize GLAD (load all OpenGL function pointers)
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return EXIT_FAILURE;
  }

  // Coordinates of the vertices of the triangle
  Vertex rectangleVertices[8] = {
      // Face 1 of square
      Vertex(Position{-0.5f, -0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),  // 0
      Vertex(Position{+0.5f, -0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),  // 1
      Vertex(Position{+0.5f, +0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),  // 2
      Vertex(Position{-0.5f, +0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),  // 3

      // Face 2 of square
      Vertex(Position{-0.5f, -0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),  // 4
      Vertex(Position{+0.5f, -0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),  // 5
      Vertex(Position{+0.5f, +0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),  // 6
      Vertex(Position{-0.5f, +0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),  // 7
  };

  // Indices of the vertices of the triangle
  unsigned int rectangleIndices[36] = {
      // Front face of square
      0, 1, 2,  // Lower triangle
      0, 2, 3,  // Upper triangle

      // Back face of square
      4, 5, 6,  // Lower triangle
      4, 6, 7,  // Upper triangle

      // Left face of square
      0, 7, 4,  // Lower triangle
      0, 3, 7,  // Upper triangle

      // Right face of square
      1, 2, 6,  // Lower triangle
      1, 5, 6,  // Upper triangle

      // Top face of square
      2, 3, 6,  // Lower triangle
      3, 6, 7,  // Upper triangle

      // Bottom face of square
      0, 5, 1,  // Lower triangle
      0, 4, 5,  // Upper triangle
  };

  // Create a Vertex Array Object
  VertexArray VAO;

  // Create a Vertex Buffer Object
  VertexBuffer VBO(rectangleVertices, sizeof(rectangleVertices));

  // Create a Vertex Buffer Layout (how to read the VBO)
  VertexBufferLayout layout(sizeof(Vertex));
  layout.push(4, GL_FLOAT, offsetof(Vertex, position));       // Position
  layout.push(4, GL_FLOAT, offsetof(Vertex, color));          // Color
  layout.push(2, GL_FLOAT, offsetof(Vertex, textureCoords));  // Texture Coords

  VAO.addVertexBufferObject(VBO, layout);

  // Create an Element Buffer Object (index buffer)
  IndexBuffer IBO(rectangleIndices, sizeof(rectangleIndices));

  // Generate a program with the vertex and the fragment shader
  Shader shaderProgram;

  // Check if the program was successfully created
  if (shaderProgram.error) {
    std::cout << "Failed to generate shader program" << std::endl;
    return EXIT_FAILURE;
  }

  // Loading the texture
  int sideTextureIndex = 0;
  Texture texture("rsc/textures/side.jpg");
  texture.bind(sideTextureIndex);
  shaderProgram.updateUniform("uTexture", sideTextureIndex);

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Check for the user input
    processInput(window);

    // Clear the screen
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
