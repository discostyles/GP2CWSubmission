#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;

struct DirectionalLight
{
	vec3 direction;
	vec4 ambientColour;
	vec4 diffuseColour;
	vec4 specularColour;
};

uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform vec4 diffuseMaterialColour=vec4(0.8f,0.0f,0.0f,1.0f);
uniform vec4 specularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform float specularPower=25.0f;

uniform DirectionalLight directionLight;

uniform sampler2D diffuseSampler;
uniform sampler2D speclarSampler;
uniform sampler2D normalSampler;



void main()
{
	vec3 lightDir=normalize(-directionLight.direction);
	float diffuseTerm = dot(vertexNormalOut, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(vertexNormalOut, halfWayVec), specularPower);

	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//FragColor = vec4(vertexTextureCoordsOut, 0.0f, 1.0f);

	//FragColor = texture(diffuseSampler, vertexTextureCoordsOut);

	vec4 speclarTextureColour = texture(speclarSampler, vertexTextureCoordsOut);

	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);

	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColour*directionLight.diffuseColour*diffuseTerm) + (speclarTextureColour*directionLight.specularColour*specularTerm);
}
