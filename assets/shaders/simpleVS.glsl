#version 410 
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec4 vertexColor;
layout(location=2) in vec2 textureCoords;
out vec4 VertexColorOut;
out vec2 TextureCoordsOut;

uniform mat4 MVP;

void main()
{
	VertexColorOut = vertexColor;
	TextureCoordsOut = textureCoords;
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}