#ifndef __LIGHTS_HPP__
#define __LIGHTS_HPP__

// Standard Libraries
#include <iostream>
#include <string>

// Libraries imports
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

// Local imports
#include "shaders.hpp"

class LightSource {
 public:
  // Ambient light
  glm::vec3 ambientColor;
  float ambientIntensity;

  // Diffuse light
  glm::vec3 diffuseColor;
  float diffuseIntensity;

  // Specular light
  glm::vec3 specularColor;
  float specularIntensity;
  float specularRadius;

  // Position
  glm::vec3 position;

  // Attached shader
  Shader* shader;

  LightSource(Shader* s = NULL);

  void setShader(Shader* s);

  void setAmbientColor(float r, float g, float b, float intensity);

  void setDiffuseColor(float r, float g, float b, float intensity);

  void setSpecularColor(float r, float g, float b, float radius, float intensity);

  void setPosition(float x, float y, float z);
};

#endif  // __LIGHTS_HPP__