#version 330 core

in vec2 TexCoord;
			
out vec4 FragColor;

uniform bool uPng;
uniform vec4 uColor;
uniform sampler2D uTexture;

void main()
{
	if (uPng)
		FragColor = vec4(texture(uTexture, TexCoord)) * uColor;
	else
		FragColor = uColor;
}