#ifndef __TEXTURES_HPP__
#define __TEXTURES_HPP__

// Standard Libraries
#include <iostream>
#include <string>

// Libraries imports
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>  // STB: https://github.com/nothings/stb/raw/master/stb_image.h

// Local imports
#include "errors.hpp"

class Texture {
 private:
  int textureIndex;
  unsigned int textureID;
  std::string texturePath;
  unsigned char* textureBuffer;
  unsigned int textureDimension;
  unsigned int textureType;
  std::string textureTypeStr;

  // Texture data
  int width;
  int height;
  int nChannels;

 public:
  Texture(std::string _texturePath, unsigned int _textureType = 0, std::string _textureTypeStr = "",
          int _textureIndex = -1, unsigned int _textureDimension = GL_TEXTURE_2D);
  ~Texture();

  void bind();
  void unbind();
  void activate();
  void bindAndActive();
  void deactivate();

  inline unsigned int getWidth();
  inline unsigned int getHeight();
  inline unsigned int getNumberOfChannels();

  int getTextureIndex();
  unsigned int getTextureID();
  std::string getPath();
  inline unsigned char* getBuffer();
  inline unsigned int getDimension();
  inline unsigned int getType();
  std::string getTypeStr();

  inline void setTextureWrapS(unsigned int wrap = GL_REPEAT);
  inline void setTextureWrapT(unsigned int wrap = GL_REPEAT);
  inline void setTextureMinFilter(unsigned int filter = GL_LINEAR_MIPMAP_LINEAR);
  inline void setTextureMagFilter(unsigned int filter = GL_NEAREST_MIPMAP_NEAREST);
};

#endif  // __TEXTURES_HPP__