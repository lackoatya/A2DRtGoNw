#version 330 core
in vec3 textColor;
in vec2 textTexCoord;

out vec4 color;

uniform sampler2D textTexture;

void main()
{
    color = texture(textTexture, textTexCoord);
}
 
/*
varying vec2 texcoord;
uniform sampler2D tex;
uniform vec4 color;
 
void main(void) {
  gl_FragColor = vec4(1, 1, 1, texture2D(tex, texcoord).a) * color;
}
*/