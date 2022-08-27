#version 330 core
layout(location = 0)in vec2 position;
layout(location = 1)in vec4 vertexColor;

out vec4 vertexColors;

void main()
{
  gl_Position = vec4(position.xy, 0.0, 1.0);
  vertexColors = vertexColor;
}
