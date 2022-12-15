#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;

out vec4 Color;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
  gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
  Color = color;
  TexCoord = texCoord;
  FragPos = vec3(model * vec4(pos, 1.0));
  Normal = vec3(model * vec4(normal, 1.0));
}