#version 330 core
in vec3 wallColor;
in vec2 wallTexCoord;

out vec4 color;

uniform sampler2D wallTexture;

void main()
{
    color = texture(wallTexture, wallTexCoord);
}