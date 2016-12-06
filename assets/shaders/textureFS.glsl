#version 410
out vec4 FragColor;
in vec4 VertexColorOut;
in vec2 TextureCoordsOut;

uniform sampler2D diffuseSampler;

void main()
{
	FragColor = texture(diffuseSampler, TextureCoordsOut);
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}