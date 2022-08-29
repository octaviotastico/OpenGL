#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

// Libraries imports
#include <GLFW/glfw3.h>

class VertexBuffer {
 private:
  unsigned int VBO_ID;

 public:
  // Create a new VertexBuffer object.
  VertexBuffer(const void* data, unsigned int size);
  // Delete created VertexBuffer object.
  ~VertexBuffer();

  // Bind VertexBuffer object.
  void bind() const;
  // Unbind VertexBuffer object.
  void unbind() const;
};

#endif  // __VERTEX_BUFFER_HPP__