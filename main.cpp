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
  Vertex rectangleVertices[4] = {
      Vertex(Position{-0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),
      Vertex(Position{+0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),
      Vertex(Position{+0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),
      Vertex(Position{-0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),
  };

  // Indices of the vertices of the triangle
  unsigned int rectangleIndices[] = {
      0, 1, 2,  // First triangle
      0, 2, 3,  // Second triangle
  };

  // Create a Vertex Array Object
  VertexArray VAO;
  /* This replaces:
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
  */

  // Create a Vertex Buffer Object
  VertexBuffer VBO(rectangleVertices, sizeof(rectangleVertices));
  /* This replaces:
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);
  */

  // Create a Vertex Buffer Layout (how to read the VBO)
  VertexBufferLayout layout(sizeof(Vertex));
  layout.push(4, GL_FLOAT, offsetof(Vertex, position));       // Position
  layout.push(4, GL_FLOAT, offsetof(Vertex, color));          // Color
  layout.push(2, GL_FLOAT, offsetof(Vertex, textureCoords));  // Texture Coords
  /* This replaces:
    .. -> Position
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    .. -> Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    .. -> Texture Coords
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,
    textureCoords)); glEnableVertexAttribArray(2);
  */

  VAO.addVertexBufferObject(VBO, layout);

  // Create an Element Buffer Object (index buffer)
  IndexBuffer IBO(rectangleIndices, sizeof(rectangleIndices));
  /* This replaces:
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);
  */

  // Generate a program with the vertex and the fragment shader
  // unsigned int programID = generateShaderProgram();
  Shader shaderProgram;

  // Check if the program was successfully created
  if (shaderProgram.error) {
    std::cout << "Failed to generate shader program" << std::endl;
    return EXIT_FAILURE;
  }

  // Variables for updating uniform uColor
  float red = 1.0f, green = 0.25f, blue = 0.0f;
  float change = 0.01f;

  // Loading the texture
  Texture texture("rsc/textures/side.jpg");
  texture.bind();
  shaderProgram.updateUniform("uTexture", 0);

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Check for the user input
    processInput(window);

    // Clear the screen
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color of the rectangle
    shaderProgram.updateUniform("uColor", red, green, blue, 1.0f);

    // Update color
    if (red > 1.0f || red < 0.0f) {
      change *= -1.0f;
    }
    red -= change;
    blue += change;

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
