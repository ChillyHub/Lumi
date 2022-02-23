#version 330 core

in vec2 TexCoord;
			
out vec4 FragColor;

uniform bool uPng;
uniform vec3 uColor;
uniform sampler2D uTexture;

void main()
{
	if (uPng)
		FragColor = vec4(texture(uTexture, TexCoord));
	else
		FragColor = vec4(uColor, 1.0);
}