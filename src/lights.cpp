#include "lights.hpp"

LightSource::LightSource(Shader* s) { shader = s; }

void LightSource::setShader(Shader* s) { shader = s; }

void LightSource::setAmbientColor(float r, float g, float b, float intensity) {
  ambientColor = glm::vec3(r, g, b);
  ambientIntensity = intensity;

  (*shader).updateUniform("uLightAmbientColor", ambientColor);
  (*shader).updateUniform("uLightAmbientIntensity", ambientIntensity);
}

void LightSource::setDiffuseColor(float r, float g, float b, float intensity) {
  diffuseColor = glm::vec3(r, g, b);
  diffuseIntensity = intensity;

  (*shader).updateUniform("uLightDiffuseColor", diffuseColor);
  (*shader).updateUniform("uLightDiffuseIntensity", diffuseIntensity);
}

void LightSource::setSpecularColor(float r, float g, float b, float radius, float intensity) {
  specularColor = glm::vec3(r, g, b);
  specularIntensity = intensity;
  specularRadius = radius;

  (*shader).updateUniform("uLightSpecularColor", specularColor);
  (*shader).updateUniform("uLightSpecularIntensity", specularIntensity);
  (*shader).updateUniform("uLightSpecularRadius", specularRadius);
}

void LightSource::setPosition(float x, float y, float z) {
  position = glm::vec3(x, y, z);

  (*shader).updateUniform("uLightPosition", position);
}
