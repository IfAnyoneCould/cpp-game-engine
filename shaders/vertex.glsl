#version 330 core
layout (location = 0) in vec2 aPos;

out vec2 texCoord;

uniform vec2 uvSize;
uniform vec2 uvOffset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos,0.0, 1.0);
    texCoord = aPos * uvSize + uvOffset;
}