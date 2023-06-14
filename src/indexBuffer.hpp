#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__

// Libraries imports
#include "../dependencies/include/GLFW/glfw3.h"

class IndexBuffer {
 private:
  unsigned int EBO_ID;
  unsigned int size;

 public:
  IndexBuffer(const void* data, unsigned int size);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;

  inline unsigned int getSize() const { return size; }
};

#endif  // __INDEX_BUFFER_HPP__