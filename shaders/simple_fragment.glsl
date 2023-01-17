#version 330 core

in vec4 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D normalMap0;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
  // Ambient
  float ambientStrength = 0.5;
  vec3 ambient = ambientStrength * lightColor;

  // Diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float strength = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = strength * lightColor;

  // Specular
  float specularStrength = 0.5;
  vec3 viewDirection = normalize(viewPos - FragPos);
  vec3 reflectDirection = reflect(-lightDir, norm);
  float intensity = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
  vec3 specular = specularStrength * intensity * lightColor;

  vec4 lighting = vec4(diffuse + specular + ambient, 1.0);

  FragColor = texture(texture0, TexCoord) * lighting;
}