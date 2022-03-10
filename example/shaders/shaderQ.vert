#version 330 core
			
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 uProjection;
uniform mat4 uView;

void main()
{
	gl_Position = uProjection * uView * vec4(aPosition, 1.0);
	TexCoord = aTexCoord;
}