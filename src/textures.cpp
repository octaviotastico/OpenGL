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

Texture::Texture(std::string _texturePath, unsigned int _textureType, std::string _textureTypeStr,
                 int _textureIndex, unsigned int _textureDimension) {
  // Load the texture
  texturePath = _texturePath;
  textureType = _textureType;
  textureTypeStr = _textureTypeStr;
  textureDimension = _textureDimension;
  textureIndex = _textureIndex;
  stbi_set_flip_vertically_on_load(true);
  textureBuffer = stbi_load(texturePath.c_str(), &width, &height, &nChannels, 4);
  glCheckError();

  // Check if the texture was loaded
  if (textureBuffer == NULL) {
    std::cout << "Failed to load texture: " << texturePath << std::endl;
    return;
  }

  // Check if the texture index was specified
  if (textureIndex == -1) {
    textureIndex = globalIndex;
    globalIndex++;
  }

  // Generate the texture
  glGenTextures(1, &textureID);
  glBindTexture(textureDimension, textureID);
  glCheckError();

  // Configure the texture
  // -> Wrapping
  glTexParameteri(textureDimension, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(textureDimension, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glCheckError();
  // -> Filtering
  glTexParameteri(textureDimension, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glCheckError();
  glTexParameteri(textureDimension, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glCheckError();

  // Send the texture to the GPU
  glTexImage2D(textureDimension, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
  glCheckError();

  // Generate the mipmaps
  glGenerateMipmap(textureDimension);
  glCheckError();

  // Free the texture buffer and unbind the texture
  stbi_image_free(textureBuffer);
  glBindTexture(textureDimension, 0);
  glCheckError();
}

Texture::~Texture() { glDeleteTextures(1, &textureID); }

void Texture::bind() {
  std::cout << "Texture dimension: " << textureDimension << " textureID " << textureID << std::endl;
  glCheckError();
  glBindTexture(textureDimension, textureID);
  glCheckError();
}
void Texture::unbind() { glBindTexture(textureDimension, 0); }

void Texture::activate() {
  // std::cout << "Activating texture: " << textureIndex << std::endl;
  glActiveTexture(GL_TEXTURE0 + textureIndex);
}

void Texture::deactivate() { glActiveTexture(GL_TEXTURE0); }

void Texture::bindAndActive() {
  glActiveTexture(GL_TEXTURE0 + textureIndex);
  glBindTexture(textureDimension, textureID);
}

inline unsigned int Texture::getWidth() { return width; }
inline unsigned int Texture::getHeight() { return height; }
inline unsigned int Texture::getNumberOfChannels() { return nChannels; }

int Texture::getTextureIndex() { return textureIndex; }
unsigned int Texture::getTextureID() { return textureID; }
std::string Texture::getPath() { return texturePath; }
inline unsigned char* Texture::getBuffer() { return textureBuffer; }
inline unsigned int Texture::getDimension() { return textureDimension; }
inline unsigned int Texture::getType() { return textureDimension; }
std::string Texture::getTypeStr() { return textureTypeStr; }

void Texture::setTextureWrapS(unsigned int wrap) {
  glBindTexture(textureDimension, textureID);
  glTexParameteri(textureDimension, GL_TEXTURE_WRAP_S, wrap);
  glBindTexture(textureDimension, 0);
}

void Texture::setTextureWrapT(unsigned int wrap) {
  glBindTexture(textureDimension, textureID);
  glTexParameteri(textureDimension, GL_TEXTURE_WRAP_T, wrap);
  glBindTexture(textureDimension, 0);
}

void Texture::setTextureMinFilter(unsigned int filter) {
  glBindTexture(textureDimension, textureID);
  glTexParameteri(textureDimension, GL_TEXTURE_MIN_FILTER, filter);
  glBindTexture(textureDimension, 0);
}

void Texture::setTextureMagFilter(unsigned int filter) {
  glBindTexture(textureDimension, textureID);
  glTexParameteri(textureDimension, GL_TEXTURE_MAG_FILTER, filter);
  glBindTexture(textureDimension, 0);
}