#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <iostream>
#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

// class Vec3Class {
//   public:
//     float vec3[3];
//     Vec3Class(float x, float y, float z) {
//         vec3[0] = x;
//         vec3[1] = y;
//         vec3[2] = z;
//     }
// };

// // Normal Class is a Vec3Class
// class NormalClass : public Vec3Class {
//   public:
//     NormalClass(float x, float y, float z) : Vec3Class(x, y, z) {}
// };

class Position {
 public:
  float position[4];
  Position(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
    position[3] = w;
  }
};

class Color {
 public:
  float color[4];
  Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
  }
};

class TextureCoords {
 public:
  float texture[2];
  TextureCoords(float s = 0.0f, float t = 0.0f) {
    texture[0] = s;
    texture[1] = t;
  }
};

class Normal {
 public:
  float normal[3];
  Normal(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
    normal[0] = x;
    normal[1] = y;
    normal[2] = z;
  }
};

class Tangent {
 public:
  float tangent[3];
  Tangent(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
    tangent[0] = x;
    tangent[1] = y;
    tangent[2] = z;
  }
};

class Bitangent {
 public:
  float bitangent[3];
  Bitangent(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
    bitangent[0] = x;
    bitangent[1] = y;
    bitangent[2] = z;
  }
};

class Vertex {
 public:
  Position position;
  Color color;
  TextureCoords textureCoords;
  Normal normal;
  Tangent tangent;
  Bitangent bitangent;

  int m_BoneIDs[MAX_BONE_INFLUENCE];    // Bone indices which will influence this vertex
  float m_Weights[MAX_BONE_INFLUENCE];  // Weights from each bone

  // Create a new Vertex object.
  Vertex() {}
  Vertex(Position p) { position = p; }
  Vertex(Position p, Color c) {
    position = p;
    color = c;
  }
  Vertex(Position p, Color c, TextureCoords t) {
    position = p;
    color = c;
    textureCoords = t;
  }
  Vertex(Position p, Color c, TextureCoords t, Normal n) {
    position = p;
    color = c;
    textureCoords = t;
    normal = n;
  }
  Vertex(Position p, Color c, TextureCoords t, Normal n, Tangent tan) {
    position = p;
    color = c;
    textureCoords = t;
    normal = n;
    tangent = tan;
  }
  Vertex(Position p, Color c, TextureCoords t, Normal n, Tangent tan, Bitangent bitan) {
    position = p;
    color = c;
    textureCoords = t;
    normal = n;
    tangent = tan;
    bitangent = bitan;
  }

  void print() {
    std::cout << "Position: " << position.position[0] << ", " << position.position[1] << ", "
              << position.position[2] << ", " << position.position[3] << std::endl;
    std::cout << "Color: " << color.color[0] << ", " << color.color[1] << ", " << color.color[2] << ", "
              << color.color[3] << std::endl;
    std::cout << "Texture Coords: " << textureCoords.texture[0] << ", " << textureCoords.texture[1]
              << std::endl;
    std::cout << "Normal: " << normal.normal[0] << ", " << normal.normal[1] << ", " << normal.normal[2]
              << std::endl;
    std::cout << "Tangent: " << tangent.tangent[0] << ", " << tangent.tangent[1] << ", "
              << tangent.tangent[2] << std::endl;
    std::cout << "Bitangent: " << bitangent.bitangent[0] << ", " << bitangent.bitangent[1] << ", "
              << bitangent.bitangent[2] << std::endl;
  }
};

#endif  // __VERTEX_HPP__