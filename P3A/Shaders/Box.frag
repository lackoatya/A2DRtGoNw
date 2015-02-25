#version 330 core
in vec3 boxColor;
in vec2 boxTexCoord;

out vec4 color;

uniform sampler2D boxTexture;

void main()
{
    color = texture(boxTexture, boxTexCoord);
	//gl_FragColor = vec4(color.xyz, (texture(boxTexture, boxTexCoord).a * color.w));
}