#version 330 core
// Input variables
layout(location = 0)in vec4 position;
layout(location = 1)in vec4 vertexColor;

// Output variables, for the fragment shader
out vec4 vertexColors;

void main()
{
  gl_Position = position;
  vertexColors = vertexColor;
}
