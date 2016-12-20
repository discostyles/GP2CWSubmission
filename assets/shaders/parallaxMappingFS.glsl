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

uniform float bias = 0.03f;
uniform float scale = 0.015f;

uniform DirectionalLight directionLight;

uniform sampler2D diffuseSampler;
uniform sampler2D speclarSampler;
uniform sampler2D normalSampler;
uniform sampler2D heightMap;
uniform sampler2D fbo_Texture;


void main()
{
	float height = texture(heightMap, vertexTextureCoordsOut).x;

	//vec2 correctedTexCoord = vertexTextureCoordsOut;

	//vec2 correctedTexCoords = scale*vertexTextureCoords*height-bias;
	//correctedTexCoords = vertexTextureCoordsOut - correctedTexCoords;
	vec2 correctedTexCoords = vertexTextureCoordsOut;

	vec3 bumpNormals = normalize(((texture(normalSampler, correctedTexCoords).xyz))*2.0f - 1.0f);

	//bumpNormals = normalize((bumpNormals.x * 2.0f) - 1.0f, (bumpNormals.y * 2.0f) - 1.0f, (bumpNormals.z * 2.0f) - 1.0f);

	vec3 lightDir=normalize(-directionLight.direction);
	float diffuseTerm = dot(bumpNormals, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);

	vec4 speclarTextureColour = texture(speclarSampler, correctedTexCoords);

	vec4 diffuseTextureColour = texture(diffuseSampler, correctedTexCoords);

	FragColor = texture2D(fbo_Texture, vertexTextureCoordsOut);

	//FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColour*directionLight.diffuseColour*diffuseTerm) + (speclarTextureColour*directionLight.specularColour*specularTerm);
}
