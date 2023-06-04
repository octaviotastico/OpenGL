#ifndef __VERTEX_ARRAY_HPP__
#define __VERTEX_ARRAY_HPP__

// Libraries imports
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// Local imports
#include "errors.hpp"
#include "vertex.hpp"
#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

class VertexArray {
 public:
  // ID of VertexArray object.
  unsigned int VAO_ID;

  // Create a new VertexArray object.
  VertexArray();

  // Delete created VertexArray object.
  ~VertexArray();

  // Add a VertexBuffer to the VertexArray object.
  void addVertexBufferObject(const VertexBuffer& vbo, const VertexBufferLayout& layout);

  // Bind created VertexArray object.
  void bind();

  // Unbind created VertexArray object.
  void unbind();

  // Draw the VertexArray object.
  void draw(unsigned int count);
};

#endif  // __VERTEX_ARRAY_HPP__