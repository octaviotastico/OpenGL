#include "vertex.hpp"

void Vertex::setPosition(float x, float y, float z, float w) {
  positionArray[0] = x;
  positionArray[1] = y;
  positionArray[2] = z;
  positionArray[3] = w;
}

void Vertex::setColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
  colorArray[3] = a;
}

void Vertex::setTexture(float u = 0.0f, float v = 0.0f, float w = 0.0f) {
  textureArray[0] = u;
  textureArray[1] = v;
  textureArray[2] = w;
}

float* Vertex::getPosition() { return positionArray; }
float* Vertex::getColor() { return colorArray; }
float* Vertex::getTexture() { return textureArray; }