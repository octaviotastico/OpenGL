#version 330 core
// Input variables
layout(location = 0)in vec4 position;
layout(location = 1)in vec4 vertexColor;
layout(location = 2)in vec2 textureCoord;
layout(location = 3)in vec3 normal;
layout(location = 4)in vec3 vertexTangent;
layout(location = 5)in vec3 vertexBitangent;
layout(location = 6)in vec4 boneIDs;
layout(location = 7)in vec4 boneWeights;

// Uniform variables for matrices
uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uCameraView;

// Output variables, for the fragment shader
out vec4 vertexColors;
out vec2 textureCoords;
out vec3 normals;

void main()
{
  gl_Position = uProjection * uCameraView * uModel * position;
  vertexColors = vertexColor;
  textureCoords = textureCoord;
  normals = normal;
}
