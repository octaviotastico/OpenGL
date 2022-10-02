#ifndef __MESH_H__
#define __MESH_H__

// Standard Libraries
#include <string>
#include <vector>

// Libraries imports
#include <GLAD/glad.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// Local imports
#include "indexBuffer.hpp"
#include "shaders.hpp"
#include "textures.hpp"
#include "vertex.hpp"
#include "vertexArray.hpp"
#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

class Mesh {
 public:
  // Constructor
  Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t) {
    vertices = v;
    textures = t;
    indices = i;

    // Now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
  }

  // Render the mesh
  void Draw(Shader &shader) {
    // Bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++) {
      // Active proper texture unit before binding retrieve
      // texture number (the N in diffuse_textureN).
      textures[i].activate();

      std::string number;
      std::string name = textures[i].getTypeStr();
      if (name == "texture_diffuse")
        number = std::to_string(diffuseNr++);
      else if (name == "texture_specular")
        number = std::to_string(specularNr++);  // Transfer unsigned int to string.
      else if (name == "texture_normal")
        number = std::to_string(normalNr++);  // Transfer unsigned int to string.
      else if (name == "texture_height")
        number = std::to_string(heightNr++);  // Transfer unsigned int to string.

      // Now set the sampler to the correct texture unit.
      // TODO: Check this uniforms
      glUniform1i(glGetUniformLocation(shader.getID(), (name + number).c_str()), i);
      // And finally bind the texture.
      glBindTexture(GL_TEXTURE_2D, textures[i].getTextureID());
    }

    // Draw mesh.
    VAO.bind();
    VAO.draw(IBO.getSize());
    VAO.unbind();

    // Always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
  }

 private:
  // Mesh Data
  std::vector<Vertex> vertices;
  std::vector<Texture> textures;
  std::vector<unsigned int> indices;

  // Data structures
  VertexArray VAO;
  VertexBuffer VBO;
  IndexBuffer IBO;
  VertexBufferLayout layout;

  // Initializes all the buffer objects/arrays.
  void setupMesh() {
    // Bind VAO.
    VAO.bind();

    // Setup and bind VBO.
    VBO.setup(vertices);

    // Set stride to layout.
    layout.setStride(sizeof(Vertex));

    // Set the vertex attribute pointers.
    layout.push(4, GL_FLOAT, offsetof(Vertex, position));       // Position.
    layout.push(4, GL_FLOAT, offsetof(Vertex, color));          // Color.
    layout.push(2, GL_FLOAT, offsetof(Vertex, textureCoords));  // Texture coordinates.
    layout.push(3, GL_FLOAT, offsetof(Vertex, normal));         // Normal.
    layout.push(3, GL_FLOAT, offsetof(Vertex, tangent));        // Tangent.
    layout.push(3, GL_FLOAT, offsetof(Vertex, bitangent));      // Bitangent.
    layout.push(4, GL_INT, offsetof(Vertex, m_BoneIDs));        // Bone indices.
    layout.push(4, GL_FLOAT, offsetof(Vertex, m_Weights));      // Bone weights.

    // Add the layout to the mesh VAO.
    VAO.addVertexBufferObject(VBO, layout);

    // Create an index buffer object for the mesh.
    IBO.setup(indices);
  }
};

#endif  // __MESH_H__
