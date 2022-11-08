#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;

out vec4 Color;
out vec2 TexCoord;

void main()
{
   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
   Color = color;
   TexCoord = texCoord;
}