#include "textures.hpp"

/*
  Texture wrapping modes:
  GL_REPEAT
  GL_MIRRORED_REPEAT
  GL_CLAMP_TO_EDGE
  GL_CLAMP_TO_BORDER

  Texture filtering modes:
  GL_NEAREST
  GL_LINEAR

  Texture mipmap modes:
  GL_NEAREST_MIPMAP_NEAREST
  GL_LINEAR_MIPMAP_NEAREST
  GL_NEAREST_MIPMAP_LINEAR
  GL_LINEAR_MIPMAP_LINEAR
*/

Texture::Texture(std::string path, unsigned int type) {
  // Load the texture
  texturePath = path;
  textureType = type;
  stbi_set_flip_vertically_on_load(true);
  textureBuffer = stbi_load(path.c_str(), &width, &height, &nChannels, 4);
  if (textureBuffer == NULL) {
    std::cout << "Failed to load texture: " << path << std::endl;
    return;
  }

  // Generate the texture
  glGenTextures(1, &textureID);
  glBindTexture(textureType, textureID);

  // Configure the texture
  // -> Wrapping
  glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // -> Filtering
  glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  // Send the texture to the GPU
  glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);

  // Generate the mipmaps
  glGenerateMipmap(textureType);

  // Free the texture buffer and unbind the texture
  stbi_image_free(textureBuffer);
  glBindTexture(textureType, 0);
}

Texture::~Texture() { glDeleteTextures(1, &textureID); }

void Texture::bind(unsigned int activeTexture) {
  glActiveTexture(GL_TEXTURE0 + activeTexture);
  glBindTexture(textureType, textureID);
}

void Texture::unbind() { glBindTexture(textureType, 0); }

inline unsigned int Texture::getID() { return textureID; }
inline unsigned int Texture::getWidth() { return width; }
inline unsigned int Texture::getHeight() { return height; }
inline unsigned int Texture::getNumberOfChannels() { return nChannels; }
inline std::string Texture::getPath() { return texturePath; }
inline unsigned char* Texture::getBuffer() { return textureBuffer; }