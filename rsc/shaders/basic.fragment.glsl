#version 330 core
layout(location = 0)out vec4 color;
in vec4 vertexColors;
uniform vec4 uColor;

void main()
{
  color = vertexColors;
}
