#version 330 core
// Input variables
in vec4 vertexColors;

// Output variables
layout(location = 0)out vec4 color;

// Global variables
uniform vec4 uColor;

void main()
{
  color = vertexColors;
}
