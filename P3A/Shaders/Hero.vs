#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 heroColor;
out vec2 heroTexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(position, 0.0f, 1.0f);
	heroColor = color;
	heroTexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}