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
  int textureIndex;

  // Texture data
  int width;
  int height;
  int nChannels;

 public:
  Texture(std::string path, unsigned int type = GL_TEXTURE_2D, int index = 0.0f);
  ~Texture();

  void bind();
  void unbind();

  inline unsigned int getWidth();
  inline unsigned int getHeight();
  inline unsigned int getNumberOfChannels();

  inline unsigned int getID();
  inline std::string getPath();
  inline unsigned char* getBuffer();
  inline unsigned int getTextureType();
  int getTextureIndex();

  inline void setTextureWrapS(unsigned int wrap = GL_REPEAT);
  inline void setTextureWrapT(unsigned int wrap = GL_REPEAT);
  inline void setTextureMinFilter(unsigned int filter = GL_LINEAR_MIPMAP_LINEAR);
  inline void setTextureMagFilter(unsigned int filter = GL_NEAREST_MIPMAP_NEAREST);
};

#endif  // __TEXTURES_HPP__