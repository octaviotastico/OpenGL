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
  Vertex rectangleVertices[24] = {

      // -------- Front and Back ------- //

      Vertex(Position{-0.5f, -0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),  // 0
      Vertex(Position{+0.5f, -0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),  // 1
      Vertex(Position{+0.5f, +0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),  // 2
      Vertex(Position{-0.5f, +0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),  // 3

      Vertex(Position{-0.5f, -0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),  // 4
      Vertex(Position{+0.5f, -0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),  // 5
      Vertex(Position{+0.5f, +0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),  // 6
      Vertex(Position{-0.5f, +0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),  // 7

      // -------- Left and Right ------- //

      Vertex(Position{-0.5f, -0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),  // 8
      Vertex(Position{+0.5f, -0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),  // 9
      Vertex(Position{+0.5f, +0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),  // 10
      Vertex(Position{-0.5f, +0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),  // 11

      Vertex(Position{-0.5f, -0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),  // 12
      Vertex(Position{+0.5f, -0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),  // 13
      Vertex(Position{+0.5f, +0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),  // 14
      Vertex(Position{-0.5f, +0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),  // 15

      // -------- Top and Bottom ------- //

      Vertex(Position{-0.5f, -0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),  // 16
      Vertex(Position{+0.5f, -0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),  // 17
      Vertex(Position{+0.5f, +0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 0.0f}),  // 18
      Vertex(Position{-0.5f, +0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 0.0f}),  // 19

      Vertex(Position{-0.5f, -0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),  // 20
      Vertex(Position{+0.5f, -0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),  // 21
      Vertex(Position{+0.5f, +0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{1.0f, 1.0f}),  // 22
      Vertex(Position{-0.5f, +0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{0.0f, 1.0f}),  // 23

  };

  // Indices of the vertices of the triangle
  unsigned int indicesCount = 36;
  unsigned int rectangleIndices[36] = {
      // Front face of square
      0, 1, 2,  // Lower triangle
      0, 2, 3,  // Upper triangle

      // Back face of square
      4, 5, 7,  // Lower triangle
      5, 6, 7,  // Upper triangle

      // Left face of square
      8, 11, 12,   // Lower triangle
      11, 12, 15,  // Upper triangle

      // Right face of square
      9, 13, 14,  // Lower triangle
      9, 10, 14,  // Upper triangle

      // Top face of square
      18, 19, 22,  // Lower triangle
      19, 22, 23,  // Upper triangle

      // Bottom face of square
      16, 17, 20,  // Lower triangle
      17, 20, 21,  // Upper triangle
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

  // Testing stuff
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Enable depth (enables the Z-buffer)
  glEnable(GL_DEPTH_TEST);

  // Create transformations matrices
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  // Rotate it by the Y axis
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

  // Send the transformation matrices to the shader
  shaderProgram.updateUniform("uView", view);
  shaderProgram.updateUniform("uProjection", projection);

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Check for the user input
    processInput(window);

    // Color for clearing the screen
    glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
    // Clears the screen and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * 100), glm::vec3(0.25f, 1.0f, 0.0f));
    shaderProgram.updateUniform("uModel", model);

    // Draw the triangle
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

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
