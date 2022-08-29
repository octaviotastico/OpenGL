#include "indexBuffer.hpp"

IndexBuffer::IndexBuffer(const void* indices, unsigned int count) : count(count) {
  glGenBuffers(1, &EBO_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &EBO_ID); }

void IndexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, EBO_ID); }

void IndexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
