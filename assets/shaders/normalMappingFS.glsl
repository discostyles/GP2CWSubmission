#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;
in vec3 lightDirectionOut;

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
//	vec3 bumpNormals = normalize(((texture(normalSampler, vertexTextureCoordsOut).xyz))*2.0f - 1.0f);

	bumpNormals = normalize((bumpNormals.x * 2.0f) - 1.0f, (bumpNormals.y * 2.0f) - 1.0f, (bumpNormals.z * 2.0f) - 1.0f);

	vec3 lightDir=normalize(-directionLight.direction);
	float diffuseTerm = dot(bumpNormals, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);

	vec4 speclarTextureColour = texture(speclarSampler, vertexTextureCoordsOut);

	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);

	vertexNormalOut = bumpNormals; // LUL

	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColour*directionLight.diffuseColour*diffuseTerm) + (speclarTextureColour*directionLight.specularColour*specularTerm);



}
