#version 330 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TextureCoord;

out vec2 o_Position;
out vec2 o_TextureCoord;

void main()
{
   gl_Position = vec4(a_Position, 0.0, 1.0);
   o_Position = a_Position;
   o_TextureCoord = a_TextureCoord;
}
