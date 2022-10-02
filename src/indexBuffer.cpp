#include "indexBuffer.hpp"

IndexBuffer::IndexBuffer(const void* indices, unsigned int sz) { setup(indices, sz); }

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &EBO_ID); }

void IndexBuffer::setup(const void* indices, unsigned int sz) {
  size = sz;
  glGenBuffers(1, &EBO_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void IndexBuffer::setup(std::vector<unsigned int>& indices) {
  setup(&indices[0], indices.size() * sizeof(indices[0]));
}

void IndexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, EBO_ID); }

void IndexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
