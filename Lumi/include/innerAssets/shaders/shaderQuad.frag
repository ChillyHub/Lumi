#version 330 core

in vec2 TexCoord;
in vec4 Color;
in float TexIndex;
			
out vec4 FragColor;

uniform sampler2D uTextures[32];

void main()
{
	uint index = uint(TexIndex);
	FragColor = texture(uTextures[index], TexCoord) * Color;
}