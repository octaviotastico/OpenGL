#ifndef __MESH_H__
#define __MESH_H__

// Standard Libraries
#include <iostream>
#include <string>
#include <vector>

// Libraries imports
#include <GLAD/glad.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// Local imports
#include "errors.hpp"
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
    // std::cout << "[CALL] Mesh constructor" << std::endl;

    vertices = v;
    textures = t;
    indices = i;

    // Now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
    glCheckError();
  }

  // Render the mesh
  void Draw(Shader &shader) {
    // Bind shader
    shader.bind();
    glCheckError();

    // Bind appropriate textures
    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    unsigned int normalNr = 0;
    unsigned int heightNr = 0;

    for (unsigned int i = 0; i < textures.size(); i++) {
      // Active proper texture unit before binding retrieve
      // texture number (the N in diffuse_texture_N).
      Texture texture = textures[i];
      glCheckError();
      texture.activate();
      glCheckError();

      std::string number;
      std::string name = texture.getTypeStr();
      glCheckError();
      if (name == "texture_diffuse")
        number = std::to_string(diffuseNr++);
      else if (name == "texture_specular")
        number = std::to_string(specularNr++);
      else if (name == "texture_normal")
        number = std::to_string(normalNr++);
      else if (name == "texture_height")
        number = std::to_string(heightNr++);
      name += "_" + number;

      // Now set the sampler to the correct texture unit.
      shader.updateUniform(name, texture.getTextureIndex());
      glCheckError();
      // And finally bind the texture.
      texture.bind();  // HERE
      glCheckError();
    }

    // Draw mesh.
    VAO.bind();      // HERE
    glCheckError();  // HERE
    VAO.draw(IBO.getCount());
    glCheckError();

    // Always good practice to set everything back to defaults once configured.
    // glActiveTexture(GL_TEXTURE0);
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
    glCheckError();

    // std::cout << "Total of " << textures.size() << " textures." << std::endl;

    // Setup and bind VBO.
    // VBO.setup(verticesArray, sizeof(verticesArray));
    VBO.setup(vertices);
    glCheckError();

    // Set stride to layout.
    layout.setStride(sizeof(Vertex));
    glCheckError();

    // Set the vertex attribute pointers.
    layout.push(4, GL_FLOAT, offsetof(Vertex, position));       // Position.
    layout.push(4, GL_FLOAT, offsetof(Vertex, color));          // Color.
    layout.push(2, GL_FLOAT, offsetof(Vertex, textureCoords));  // Texture coordinates.
    layout.push(3, GL_FLOAT, offsetof(Vertex, normal));         // Normal.
    layout.push(3, GL_FLOAT, offsetof(Vertex, tangent));        // Tangent.
    layout.push(3, GL_FLOAT, offsetof(Vertex, bitangent));      // Bitangent.
    // layout.push(4, GL_INT, offsetof(Vertex, m_BoneIDs));        // Bone indices.
    // layout.push(4, GL_FLOAT, offsetof(Vertex, m_Weights));      // Bone weights.
    glCheckError();

    // Add the layout to the mesh VAO.
    VAO.addVertexBufferObject(VBO, layout);
    glCheckError();

    // Setup the index buffer object.
    IBO.setup(indices);
    glCheckError();

    // Debug VAO.
    // std::cout << "VAO ID: " << VAO.VAO_ID << std::endl;
    // std::cout << "VBO ID: " << VBO.VBO_ID << std::endl;
  }
};

#endif  // __MESH_H__
