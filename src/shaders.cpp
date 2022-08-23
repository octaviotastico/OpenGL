#include "shaders.hpp"

static int shaderCompilationFailed(unsigned int shader, std::string shader_type) {
  // First get compilation status
  int compile_status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

  if (compile_status == GL_FALSE) {
    int message_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &message_length);
    char* error_message = new char[message_length];
    glGetShaderInfoLog(shader, message_length, NULL, error_message);

    // If compilation failed, show error message
    std::cout << "ERROR::SHADER::" << shader_type << "::COMPILATION_FAILED" << std::endl;
    std::cout << error_message << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static unsigned int compileShader(unsigned int type, const char* source) {
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);
  return id;
}

unsigned int generateShaderProgram() {
  // Shader sources
  const char* vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec4 position;\n"

      "void main()\n"
      "{\n"
      "   gl_Position = position;\n"
      "}\n\0";

  const char* fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 color;\n"

      "void main()\n"
      "{\n"
      "   color = vec4(1.0f, 0.25f, 1.0f, 1.0f);\n"
      "}\n\0";

  // Create shaders and programs
  unsigned int programID = glCreateProgram();
  unsigned int vertexShaderID = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  unsigned int fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  // Check if the shaders were successfully created
  if (shaderCompilationFailed(vertexShaderID, "VERTEX") ||
      shaderCompilationFailed(fragmentShaderID, "FRAGMENT")) {
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
    return 0;
  }

  // Attach shaders to the program
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);
  glValidateProgram(programID);

  // Delete the shaders as they're linked into
  // the program now and no longer necessary
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  // Use the program
  glUseProgram(programID);

  return programID;
}
