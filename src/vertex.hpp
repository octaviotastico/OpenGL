#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <string>
#include <vector>

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

class Vertex {
 public:
  Position position;
  Color color;
  TextureCoords textureCoords;
  Normal normal;

  // Position Only
  Vertex(Position p) { position = p; }
  // Position and Color
  Vertex(Position p, Color c) {
    position = p;
    color = c;
  }
  // Position and Texture Coordinates
  Vertex(Position p, TextureCoords t) {
    position = p;
    textureCoords = t;
  }
  // Position, Color and Normal
  Vertex(Position p, Color c, Normal n) {
    position = p;
    color = c;
    normal = n;
  }
  // Position, Texture Coordinates and Normal
  Vertex(Position p, TextureCoords t, Normal n) {
    position = p;
    textureCoords = t;
    normal = n;
  }
};

#endif  // __VERTEX_HPP__