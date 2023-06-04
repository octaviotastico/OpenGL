#include "indexBuffer.hpp"

IndexBuffer::IndexBuffer() {}

IndexBuffer::IndexBuffer(std::vector<unsigned int> _indices) { setup(_indices); }

IndexBuffer::IndexBuffer(const void* _indices, unsigned int _size, unsigned int _count) {
  setup(_indices, _size, _count);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &EBO_ID); }

void IndexBuffer::setup(const void* _indices, unsigned int _size, unsigned int _count) {
  size = _size;
  count = _count;
  glGenBuffers(1, &EBO_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, _indices, GL_STATIC_DRAW);
}

void IndexBuffer::setup(std::vector<unsigned int> _indices) {
  setup(&_indices[0], _indices.size() * sizeof(unsigned int), _indices.size());
}

void IndexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, EBO_ID); }

void IndexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
