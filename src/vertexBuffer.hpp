#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

// Standard Libraries
#include <vector>

// Libraries imports
#include <GLFW/glfw3.h>

// Local imports
#include "vertex.hpp"

class VertexBuffer {
 private:
  unsigned int VBO_ID;

 public:
  // Create a new VertexBuffer object.
  VertexBuffer();
  VertexBuffer(std::vector<Vertex>& data);
  VertexBuffer(const void* data, unsigned int size);
  // Delete created VertexBuffer object.
  ~VertexBuffer();

  // Bind VertexBuffer object.
  void bind() const;
  // Unbind VertexBuffer object.
  void unbind() const;

  // Setup VertexBuffer object.
  void setup(const void* data, unsigned int size);
  void setup(std::vector<Vertex>& data);
};

#endif  // __VERTEX_BUFFER_HPP__