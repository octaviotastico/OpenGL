#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__

// Standard Libraries
#include <vector>

// Libraries imports
#include <GLFW/glfw3.h>

class IndexBuffer {
 private:
  unsigned int EBO_ID;
  unsigned int size;

 public:
  IndexBuffer();
  IndexBuffer(const void* data, unsigned int sz);
  ~IndexBuffer();

  void setup(const void* data, unsigned int sz);
  void setup(std::vector<unsigned int>& data);

  void bind() const;
  void unbind() const;

  inline unsigned int getSize() const { return size; }
};

#endif  // __INDEX_BUFFER_HPP__