#version 330 core

// Input variables
in vec4 vertexColors;
in vec2 textureCoords;
in vec3 normals;

// Output variables
layout(location = 0)out vec4 color;

// Global variables
uniform sampler2D uTexture;

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
  vec4 texColor = texture(uTexture, textureCoords);
  color = texColor * vec4(ambient + diffuse + specular, 1.0);
}
