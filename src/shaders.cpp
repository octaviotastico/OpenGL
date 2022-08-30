#include "shaders.hpp"

int Shader::checkShaderCompilationError(unsigned int shader, std::string shaderType) {
  // First get compilation status
  int compileStatus;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus == GL_FALSE) {
    int messageLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
    char* errorMessage = new char[messageLength];
    glGetShaderInfoLog(shader, messageLength, NULL, errorMessage);

    // If compilation failed, show error message
    std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED" << std::endl;
    std::cout << errorMessage << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int Shader::checkProgramLinkingError() {
  // First get link status
  int link_status;
  glGetProgramiv(programID, GL_LINK_STATUS, &link_status);

  if (link_status == GL_FALSE) {
    int messageLength;
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &messageLength);
    char* errorMessage = new char[messageLength];
    glGetProgramInfoLog(programID, messageLength, NULL, errorMessage);

    // If linking failed, show error message
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
    std::cout << errorMessage << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

unsigned int Shader::compileShader(unsigned int type, const char* source) {
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);
  return id;
}

void Shader::free() {
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
  glDeleteProgram(programID);
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
  // Vertex shader initialization
  vertexShaderPath = vertexPath;
  vertexShaderSource = readShaderFile(vertexShaderPath.c_str());
  vertexShaderID = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());

  // Fragment shader initialization
  fragmentShaderPath = fragmentPath;
  fragmentShaderSource = readShaderFile(fragmentShaderPath.c_str());
  fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

  // Create programs
  programID = glCreateProgram();

  // Check if the shaders were successfully created
  if (checkShaderCompilationError(vertexShaderID, "VERTEX") ||
      checkShaderCompilationError(fragmentShaderID, "FRAGMENT")) {
    error = true;
    free();
    return;
  }

  // Attach shaders to the program
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);
  glValidateProgram(programID);

  // Check if the program was successfully linked
  if (checkProgramLinkingError()) {
    error = true;
    free();
    return;
  }

  // Delete the shaders as they're linked into
  // the program now and no longer necessary
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  // Bind the program
  bind();
}

Shader::~Shader() { glDeleteProgram(programID); }

void Shader::bind() { glUseProgram(programID); }

void Shader::unbind() { glUseProgram(0); }

void Shader::updateUniform(std::string name, int v0) {
  int uniformID = glGetUniformLocation(programID, name.c_str());
  glUniform1i(uniformID, v0);
}
void Shader::updateUniform(std::string name, float v0) {
  int uniformID = glGetUniformLocation(programID, name.c_str());
  glUniform1f(uniformID, v0);
}
void Shader::updateUniform(std::string name, float v0, float v1) {
  int uniformID = glGetUniformLocation(programID, name.c_str());
  glUniform2f(uniformID, v0, v1);
}
void Shader::updateUniform(std::string name, float v0, float v1, float v2) {
  int uniformID = glGetUniformLocation(programID, name.c_str());
  glUniform3f(uniformID, v0, v1, v2);
}
void Shader::updateUniform(std::string name, float v0, float v1, float v2, float v3) {
  int uniformID = glGetUniformLocation(programID, name.c_str());
  glUniform4f(uniformID, v0, v1, v2, v3);
}