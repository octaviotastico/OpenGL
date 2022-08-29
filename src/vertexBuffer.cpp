#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer(const void* vertices, unsigned int size) {
  glGenBuffers(1, &VBO_ID);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &VBO_ID); }

void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, VBO_ID); }

void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
