// Libraries imports
#include <GLAD/glad.h>   // GLAD: https://github.com/Dav1dde/glad
#include <GLFW/glfw3.h>  // GLFW: https://es.wikipedia.org/wiki/GLFW

// Standard Libraries
#include <iostream>

// Local imports
#include "src/constants.hpp"
#include "src/shaders.hpp"
#include "src/utils.hpp"

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
  float rectanglePositions[] = {
      // Positions  // Colors (RGBA)
      -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  // Bottom Left
      +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  // Bottom Right
      +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  // Top Right
      -0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  // Top Left
  };

  unsigned int rectangleIndices[] = {
      0, 1, 2,  // First triangle
      0, 2, 3,  // Second triangle
  };

  // Create a Vertex Array Object
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Create a Vertex Buffer Object
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, 4 * 6 * sizeof(float), rectanglePositions, GL_STATIC_DRAW);

  // Create an Element Buffer Object (index buffer)
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), rectangleIndices, GL_STATIC_DRAW);

  // Vertex attributes (how to read the VBO)
  // Position
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // Color
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Generate a program with the vertex and the fragment shader
  unsigned int programID = generateShaderProgram();

  // Check if the program was successfully created
  if (programID == 0) {
    std::cout << "Failed to generate shader program" << std::endl;
    return EXIT_FAILURE;
  }

  // Use the shader program
  glUseProgram(programID);

  // Get uniform locations
  int uColor = glGetUniformLocation(programID, "uColor");
  float red = 1.0f, green = 0.25f, blue = 0.0f;
  glUniform4f(uColor, red, green, blue, 1.0f);
  float change = 0.01f;

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Check for the user input
    processInput(window);

    // Clear the screen
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color of the rectangle
    glUniform4f(uColor, red, green, blue, 1.0f);

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
  glDeleteProgram(programID);
  glfwTerminate();

  return EXIT_SUCCESS;
}
