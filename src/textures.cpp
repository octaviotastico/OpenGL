#include "textures.hpp"

unsigned int globalIndex = 0;

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

Texture::Texture(std::string path, unsigned int type, std::string typeStr, int index, unsigned int d) {
  // Load the texture
  texturePath = path;
  textureType = type;
  textureTypeStr = typeStr;
  textureDimension = d;
  textureIndex = index;
  stbi_set_flip_vertically_on_load(true);
  textureBuffer = stbi_load(path.c_str(), &width, &height, &nChannels, 4);

  // Check if the texture was loaded
  if (textureBuffer == NULL) {
    std::cout << "Failed to load texture: " << path << std::endl;
    return;
  }

  // Check if the texture index was specified
  if (textureIndex == -1) {
    textureIndex = globalIndex;
    globalIndex++;
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

void Texture::bind() { glBindTexture(textureType, textureID); }
void Texture::unbind() { glBindTexture(textureType, 0); }

void Texture::activate() { glActiveTexture(GL_TEXTURE0 + textureIndex); }

void Texture::deactivate() { glActiveTexture(GL_TEXTURE0); }

void Texture::bindAndActive() {
  glActiveTexture(GL_TEXTURE0 + textureIndex);
  glBindTexture(textureType, textureID);
}

inline unsigned int Texture::getWidth() { return width; }
inline unsigned int Texture::getHeight() { return height; }
inline unsigned int Texture::getNumberOfChannels() { return nChannels; }

int Texture::getTextureIndex() { return textureIndex; }
unsigned int Texture::getTextureID() { return textureID; }
std::string Texture::getPath() { return texturePath; }
inline unsigned char* Texture::getBuffer() { return textureBuffer; }
inline unsigned int Texture::getDimension() { return textureDimension; }
inline unsigned int Texture::getType() { return textureType; }
std::string Texture::getTypeStr() { return textureTypeStr; }

void Texture::setTextureWrapS(unsigned int wrap) {
  glBindTexture(textureType, textureID);
  glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrap);
  glBindTexture(textureType, 0);
}

void Texture::setTextureWrapT(unsigned int wrap) {
  glBindTexture(textureType, textureID);
  glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrap);
  glBindTexture(textureType, 0);
}

void Texture::setTextureMinFilter(unsigned int filter) {
  glBindTexture(textureType, textureID);
  glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filter);
  glBindTexture(textureType, 0);
}

void Texture::setTextureMagFilter(unsigned int filter) {
  glBindTexture(textureType, textureID);
  glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filter);
  glBindTexture(textureType, 0);
}