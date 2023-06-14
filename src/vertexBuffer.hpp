#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

// Libraries imports
#include "../dependencies/include/GLFW/glfw3.h"

class VertexBuffer {
 private:
  // ID of Vertex Buffer Object.
  unsigned int VBO_ID;

 public:
  // Create a new Vertex Buffer Object.
  VertexBuffer(const void* data, unsigned int size);

  // Delete created Vertex Buffer Object.
  ~VertexBuffer();

  // Bind Vertex Buffer Object.
  void bind() const;

  // Unbind Vertex Buffer Object.
  void unbind() const;
};

#endif  // __VERTEX_BUFFER_HPP__