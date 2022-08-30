#version 330 core
// Input variables
in vec4 vertexColors;
in vec2 textureCoords;

// Output variables
layout(location = 0)out vec4 color;

// Global variables
uniform sampler2D uTexture;

void main()
{
  // Texture fetch
  vec4 texColor = texture(uTexture, textureCoords);
  // color = vertexColors;
  color = texColor;
}
