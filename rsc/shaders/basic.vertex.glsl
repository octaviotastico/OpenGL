#version 330 core

// Input variables
layout(location = 0)in vec4 position;
layout(location = 1)in vec4 vertexColor;
layout(location = 2)in vec2 textureCoord;
layout(location = 3)in vec3 normal;

// Uniform variables for matrices
uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uCameraView;

// Output variables for the fragment shader
out vec4 vertexColors;
out vec2 textureCoords;
out vec3 normals;

void main()
{
  gl_Position = uProjection * uCameraView * uModel * position;
  vertexColors = vertexColor;
  textureCoords = textureCoord;
  normals = mat3(transpose(inverse(uModel))) * normal;
}
