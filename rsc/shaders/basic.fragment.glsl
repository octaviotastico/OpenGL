#version 330 core
// Input variables
in vec4 vertexColors;
in vec2 textureCoords;
in vec3 normals;

// Output variables
layout(location = 0)out vec4 color;

// Global variables
// Textures
uniform sampler2D texture_diffuse_0;
uniform sampler2D texture_specular_0;
uniform sampler2D texture_normal_0;
uniform sampler2D texture_height_0;

// Light variables
// -> Ambient light
uniform vec3 uLightAmbientColor;
uniform float uLightAmbientIntensity;
// -> Diffuse light
uniform vec3 uLightDiffuseColor;
uniform float uLightDiffuseIntensity;
// -> Specular light
uniform vec3 uLightSpecularColor;
uniform float uLightSpecularIntensity;
uniform float uLightSpecularRadius;
// -> Light position
uniform vec3 uLightPosition;

void main()
{
  // Ambient light
  vec3 ambient = uLightAmbientColor * uLightAmbientIntensity;
  
  // Diffuse light
  vec3 lightDir = normalize(uLightPosition - gl_FragCoord.xyz);
  float diff = max(dot(normals, lightDir), 0.0);
  vec3 diffuse = uLightDiffuseColor * uLightDiffuseIntensity * diff;
  
  // Specular light
  vec3 viewDir = normalize(-gl_FragCoord.xyz);
  vec3 reflectDir = reflect(-lightDir, normals);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), uLightSpecularRadius);
  vec3 specular = uLightSpecularColor * uLightSpecularIntensity * spec;
  
  // Texture fetch
  vec4 texColor = texture(texture_diffuse_0, textureCoords);
  // color = texColor * vec4(ambient + diffuse + specular, 1.0);
  
  // Just to debug (only ambient)
  color = texColor;
}
