#ifndef __VERTEX_ARRAY_HPP__
#define __VERTEX_ARRAY_HPP__

// Libraries imports
#include "../dependencies/include/GLAD/glad.h"
#include "../dependencies/include/GLFW/glfw3.h"

// Local imports
#include "vertex.hpp"
#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

class VertexArray {
 public:
  // ID of Vertex Array Object.
  unsigned int VAO_ID;

  // Create a new Vertex Array Object.
  VertexArray();

  // Delete created Vertex Array Object.
  ~VertexArray();

  // Add a Vertex Buffer Object (VBO) to the Vertex Array Object.
  void addVertexBufferObject(const VertexBuffer& vbo, const VertexBufferLayout& layout);

  // Bind created Vertex Array Object.
  void bind();

  // Unbind created Vertex Array Object.
  void unbind();

  // Draw the Vertex Array Object.
  void draw(unsigned int count);
};

#endif  // __VERTEX_ARRAY_HPP__