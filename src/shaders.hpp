#ifndef __SHADERS_HPP__
#define __SHADERS_HPP__

// Standard Libraries
#include <iostream>
#include <string>

// Libraries imports
#include <GLFW/glfw3.h>

// Local imports
#include "utils.hpp"

class Shader {
 private:
  unsigned int programID;

  // Vertex Shader
  unsigned int vertexShaderID;
  std::string vertexShaderPath;
  std::string vertexShaderSource;

  // Fragment shader
  unsigned int fragmentShaderID;
  std::string fragmentShaderPath;
  std::string fragmentShaderSource;

  // Compiles a shader
  unsigned int compileShader(unsigned int type, const char* source);

  // Check shader compilation status
  int checkShaderCompilationError(unsigned int shader, std::string shaderType);

  // Check program linking status
  int checkProgramLinkingError();

 public:
  bool error = false;

  // Constructor and destructor
  Shader(std::string vertexPath = "rsc/shaders/basic.vertex.glsl",
         std::string fragmentPath = "rsc/shaders/basic.fragment.glsl");
  ~Shader();

  // Bind and unbind the shader
  void bind();
  void unbind();

  // Free the shader program
  void free();

  // Update the shader uniforms
  void updateUniform(std::string name, int v0);
  void updateUniform(std::string name, float v0);
  void updateUniform(std::string name, float v0, float v1);
  void updateUniform(std::string name, float v0, float v1, float v2);
  void updateUniform(std::string name, float v0, float v1, float v2, float v3);
};

#endif  // __SHADERS_HPP__