#version 410
out vec4 FragColor;
in vec4 VertexColorOut;

void main()
{
	FragColor = VertexColorOut;
}