#version 330 core
in vec3 heroColor;
in vec2 heroTexCoord;

out vec4 color;

uniform sampler2D heroTexture;

void main()
{
    color = texture(heroTexture, heroTexCoord);
}