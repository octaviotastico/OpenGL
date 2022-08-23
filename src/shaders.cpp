#include "shaders.hpp"

unsigned int checkShaderCompilation(unsigned int shader, std::string shader_type) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::" << shader_type << "::COMPILATION_FAILED" << std::endl;
    std::cout << infoLog << std::endl;
    return 0;
  }

  return shader;
}

unsigned int generateVertexShader() {
  const char* vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"

      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\n\0";

  unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShaderID);

  return checkShaderCompilation(vertexShaderID, "VERTEX");
}

unsigned int generateFragmentShader() {
  const char* fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"

      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
      "}\n\0";

  unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShaderID);

  return checkShaderCompilation(fragmentShaderID, "FRAGMENT");
}

void generateShaderProgram() {
  // Create shaders and programs
  unsigned int programID = glCreateProgram();
  unsigned int vertexShaderID = generateVertexShader();
  unsigned int fragmentShaderID = generateFragmentShader();

  // Check if the shaders were successfully created
  if (vertexShaderID == 0 || fragmentShaderID == 0) {
    return;
  }

  // Attach shaders to the program
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);  // TODO: check if the program has linked correctly
  glValidateProgram(programID);

  // Delete the shaders as they're linked into
  // the program now and no longer necessary
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  // Use the program
  glUseProgram(programID);
}
