#include "vertexArray.hpp"

VertexArray::VertexArray() {
  glGenVertexArrays(1, &VAO_ID);
  glBindVertexArray(VAO_ID);
}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &VAO_ID); }

void VertexArray::addVertexBufferObject(const VertexBuffer& vbo, const VertexBufferLayout& layout) {
  // Bind the VertexArray object
  bind();
  // Bind the VertexBuffer object
  vbo.bind();

  unsigned int stride = layout.getStride();
  const auto elements = layout.getElements();

  for (int i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];
    glEnableVertexAttribArray(i);

    glVertexAttribPointer(
        i,                   // Attribute index
        element.count,       // Number of components (e.g. 4 for vec4, in RGBA)
        element.type,        // Type of the components (e.g. GL_FLOAT)
        element.normalized,  // Whether to normalize the data
        stride,  // Stride (size of the whole structure, e.g. Position + Colors ~= sizeof(Vertex))
        (const void*)(size_t)
            element.offset  // Offset of the component in the structure (e.g. offsetOf Color)
    );
  }
}

void VertexArray::bind() { glBindVertexArray(VAO_ID); }

void VertexArray::unbind() { glBindVertexArray(0); }

void VertexArray::draw(unsigned int count) {
  bind();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}