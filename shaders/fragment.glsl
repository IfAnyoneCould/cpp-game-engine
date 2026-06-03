#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform bool useTexture;
uniform vec3 color;
uniform sampler2D tex;

void main()
{
    if (useTexture) {
        FragColor = texture(tex,texCoord);
    } else {
        FragColor = vec4(color, 1.0f);
    }
}