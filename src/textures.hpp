#ifndef __TEXTURES_HPP__
#define __TEXTURES_HPP__

// Standard Libraries
#include <iostream>
#include <string>

// Libraries imports
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>  // STB: https://github.com/nothings/stb/raw/master/stb_image.h

class Texture {
 private:
  unsigned int textureID;
  std::string texturePath;
  unsigned char* textureBuffer;
  unsigned int textureType;

  // Texture data
  int width;
  int height;
  int nChannels;

 public:
  Texture(std::string path, unsigned int type = GL_TEXTURE_2D);
  ~Texture();

  void bind(unsigned int activeTexture = 0);
  void unbind();

  inline unsigned int getID();
  inline unsigned int getWidth();
  inline unsigned int getHeight();
  inline unsigned int getNumberOfChannels();
  inline std::string getPath();
  inline unsigned char* getBuffer();
};

#endif  // __TEXTURES_HPP__