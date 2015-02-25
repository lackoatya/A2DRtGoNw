#version 330 core
in vec2 textTexCoord;

uniform sampler2D textTexture;
uniform vec4 color;

void main()
{
    gl_FragColor = vec4(color.xyz, (texture(textTexture, textTexCoord).a * color.w));
	//color = texture(textTexture, textTexCoord);
}