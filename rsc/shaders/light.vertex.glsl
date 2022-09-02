#version 330 core
// Input variables
layout(location = 0)in vec4 position;

// Uniform variables for matrices
uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uCameraView;

void main()
{
  gl_Position = uProjection * uCameraView * uModel * position;
}
