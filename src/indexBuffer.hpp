#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__

// Standard Libraries
#include <iostream>
#include <vector>

// Libraries imports
#include <GLFW/glfw3.h>

class IndexBuffer {
 private:
  unsigned int EBO_ID;
  unsigned int size;
  unsigned int count;

 public:
  IndexBuffer();
  IndexBuffer(std::vector<unsigned int> _indices);
  IndexBuffer(const void* _indices, unsigned int _size, unsigned int _count);
  ~IndexBuffer();

  void setup(const void* _indices, unsigned int _size, unsigned int _count);
  void setup(std::vector<unsigned int> _indices);

  void bind() const;
  void unbind() const;

  inline unsigned int getSize() const { return size; }
  inline unsigned int getCount() const { return count; }
};

#endif  // __INDEX_BUFFER_HPP__