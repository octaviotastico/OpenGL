#ifndef __VERTEX_BUFFER_LAYOUT_HPP__
#define __VERTEX_BUFFER_LAYOUT_HPP__

// Library imports
#include <GLFW/glfw3.h>

// Standard Libraries
#include <vector>

// Local imports
#include "vertex.hpp"

class VertexBufferElement {
 public:
  unsigned int type;
  unsigned int count;
  unsigned int offset;
  unsigned int normalized;

  static unsigned int getSizeOfType(unsigned int type) {
    switch (type) {
      case GL_FLOAT:
        return sizeof(float);
      case GL_UNSIGNED_INT:
        return sizeof(unsigned int);
      case GL_UNSIGNED_BYTE:
        return sizeof(unsigned char);
    }
    return 0;
  }
};

class VertexBufferLayout {
 private:
  std::vector<VertexBufferElement> elements;
  unsigned int stride;

 public:
  // Create a new VertexBufferLayout object.
  VertexBufferLayout() : stride(0) {}

  // Delete created VertexBufferLayout object.
  ~VertexBufferLayout() {}

  // Push a new element to the VertexBufferLayout.
  void push(unsigned int count, int type, unsigned int offset = 0) {
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
    stride += count * VertexBufferElement::getSizeOfType(glType);
  }

  // Get the stride of the VertexBufferLayout.
  inline const unsigned int getStride() const { return stride; }

  // Get the elements of the VertexBufferLayout.
  inline const std::vector<VertexBufferElement>& getElements() const { return elements; }
};

#endif  // __VERTEX_BUFFER_LAYOUT_HPP__