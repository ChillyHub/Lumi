#version 400 core
			
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aTexIndex;

out vec2 TexCoord;
out vec4 Color;
out float TexIndex;
out vec3 Pos;

uniform mat4 uProjection;
uniform mat4 uView;

void main()
{
	gl_Position = uProjection * uView * vec4(aPosition, 1.0);
	TexCoord = aTexCoord;
	Color = aColor;
	TexIndex = aTexIndex;
	Pos = aPosition;
}