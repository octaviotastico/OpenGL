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
  float texture[3];
  TextureCoords(float s = 0.0f, float t = 0.0f, float r = 0.0f) {
    texture[0] = s;
    texture[1] = t;
    texture[2] = r;
  }
};

// TODO: Finish this class xD
class Texture {
 public:
  std::string texture_path;
  std::vector<TextureCoords> coords;

  Texture(TextureCoords coordsArray[]) {
    int size = sizeof(coordsArray) / sizeof(TextureCoords);
    for (int i = 0; i < size; i++) {
      coords.push_back(coordsArray[i]);
    }
  }
};

class Vertex {
 public:
  Position position;
  Color color;
  TextureCoords textureCoords;
  // Create a new Vertex object.
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
};
