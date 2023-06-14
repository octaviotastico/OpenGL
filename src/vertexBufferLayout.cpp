#include "vertexBufferLayout.hpp"

void VertexBufferLayout::push(unsigned int count, int type, unsigned int offset) {
  unsigned int glType = 0;
  unsigned int normalized = GL_FALSE;
  if (type == GL_FLOAT) {
    glType = GL_FLOAT;
  } else if (type == GL_UNSIGNED_INT) {
    glType = GL_UNSIGNED_INT;
  } else if (type == GL_UNSIGNED_BYTE) {
    glType = GL_UNSIGNED_BYTE;
    normalized = GL_TRUE;
  }

  // Push new element to the VertexBufferLayout.
  elements.push_back(VertexBufferElement{glType, count, offset, normalized});
}
