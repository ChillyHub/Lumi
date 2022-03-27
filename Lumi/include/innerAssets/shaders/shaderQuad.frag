#version 400 core

in vec2 TexCoord;
in vec4 Color;
in float TexIndex;
in vec3 Pos;
			
out vec4 FragColor;

uniform sampler2D uTextures[32];

void main()
{
	uint index = uint(TexIndex);
	vec4 texColor = Color;
	//FragColor = vec4(TexIndex - index, TexIndex - index, TexIndex - index, 1.0);

	switch(uint(TexIndex))
	{
		case  0: texColor *= texture(uTextures[ 0], TexCoord); break;
		case  1: texColor *= texture(uTextures[ 1], TexCoord); break;
		case  2: texColor *= texture(uTextures[ 2], TexCoord); break;
		case  3: texColor *= texture(uTextures[ 3], TexCoord); break;
		case  4: texColor *= texture(uTextures[ 4], TexCoord); break;
		case  5: texColor *= texture(uTextures[ 5], TexCoord); break;
		case  6: texColor *= texture(uTextures[ 6], TexCoord); break;
		case  7: texColor *= texture(uTextures[ 7], TexCoord); break;
		case  8: texColor *= texture(uTextures[ 8], TexCoord); break;
		case  9: texColor *= texture(uTextures[ 9], TexCoord); break;
		case 10: texColor *= texture(uTextures[10], TexCoord); break;
		case 11: texColor *= texture(uTextures[11], TexCoord); break;
		case 12: texColor *= texture(uTextures[12], TexCoord); break;
		case 13: texColor *= texture(uTextures[13], TexCoord); break;
		case 14: texColor *= texture(uTextures[14], TexCoord); break;
		case 15: texColor *= texture(uTextures[15], TexCoord); break;
		case 16: texColor *= texture(uTextures[16], TexCoord); break;
		case 17: texColor *= texture(uTextures[17], TexCoord); break;
		case 18: texColor *= texture(uTextures[18], TexCoord); break;
		case 19: texColor *= texture(uTextures[19], TexCoord); break;
		case 20: texColor *= texture(uTextures[20], TexCoord); break;
		case 21: texColor *= texture(uTextures[21], TexCoord); break;
		case 22: texColor *= texture(uTextures[22], TexCoord); break;
		case 23: texColor *= texture(uTextures[23], TexCoord); break;
		case 24: texColor *= texture(uTextures[24], TexCoord); break;
		case 25: texColor *= texture(uTextures[25], TexCoord); break;
		case 26: texColor *= texture(uTextures[26], TexCoord); break;
		case 27: texColor *= texture(uTextures[27], TexCoord); break;
		case 28: texColor *= texture(uTextures[28], TexCoord); break;
		case 29: texColor *= texture(uTextures[29], TexCoord); break;
		case 30: texColor *= texture(uTextures[30], TexCoord); break;
		case 31: texColor *= texture(uTextures[31], TexCoord); break;
	}
	FragColor = texColor;
}