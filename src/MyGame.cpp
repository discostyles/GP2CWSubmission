#include "MyGame.h"


const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{
	m_RotationX = 0;
}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	GameApplication::initScene();
	// initialise array of 3 vertices

	unsigned int Indices[] = { 0, 1, 2,
							   2, 3, 1};

	Vertex verts[]= 
	{{vec3(-0.5f, -0.5f, 0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},	//tri 1 face 1
	{vec3(0.5f, -0.5f, 0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
	{vec3(-0.5f, 0.5f, 0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
	//{vec3(-0.5f, 0.5f, 0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},	//tri 2 face 1
	{vec3(0.5f, 0.5f, 0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
	//{vec3(0.5f, -0.5f, 0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},

	//{ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },	//tri 1 face 1
	//{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
	//{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
	//{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },	//tri 2 face 1
	//{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
	//{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },

	//{ 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },	//tri 1 face 3 
	//{ 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	//{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	//{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },	//tri 2 face 3 
	//{ 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	//{ 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },

	//{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },	//tri 1 face 4 
	//{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	//{ -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	//{ -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },	//tri 2 face 4 
	//{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	//{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },

	//{ -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },	//tri 1 face 5 
	//{ 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	//{ -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	//{ 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },	//tri 2 face 5 
	//{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	//{ -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

	//{ -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },	//tri 1 face 6 
	//{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	//{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	//{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },	//tri 2 face 6 
	//{ 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	//{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	};
	//generate a VBO, bind it to the pipeline and fill it with information
	
	//m_TestObject = new GameObject();
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl";
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl";
	//m_TestObject->LoadShaders(vsPath, fsPath);
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/earth_diff.png";
	string speclarPath = ASSET_PATH + TEXTURE_PATH + "/earth_spec.png";
	string bumpPath = ASSET_PATH + TEXTURE_PATH + "/earth_norm.png";
	string heightPath = ASSET_PATH + TEXTURE_PATH + "/earth_height.png";
	//m_TestObject->LoadTexture(texturePath);
	//m_TestObject->CopyVertexData(verts, Indices, 4, 6);

	std::string modelPath = ASSET_PATH + MODEL_PATH + "/1h_axe.fbx";
	m_TeaPot = loadModelFromFile(modelPath);
	m_TeaPot->LoadShaders(vsPath, fsPath);
	m_TeaPot->LoadDiffuseTexture(texturePath);
	m_TeaPot->LoadSpeclarTexture(speclarPath);
	m_TeaPot->LoadNormalTexture(bumpPath);
	m_TeaPot->LoadHeightTexture(heightPath);
	m_TeaPot->SetAmbientMaterial(vec4(0.1f, 0.1f, 0.1f, 1.0f));
	m_CameraPos = vec3(0.0f, 0.0f, 15.0f);
	m_LightDirection = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_DiffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void MyGame::destroyScene()
{
	GameApplication::destroyScene();
	m_TeaPot->OnDestroy();













}

void MyGame::render()
{
	//glGenTextures(1, &depthMap);
	//glBindTexture(GL_TEXTURE_2D, depthMap);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
	//	SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glBindFramebuffer(GL_FRAMEBUFFER, m_DepthFBO);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GameApplication::render();
	GLuint currentShader = m_TeaPot->GetShaderProgram();
	glUseProgram(currentShader);
	GLint ViewLocation = glGetUniformLocation(currentShader, "cameraPos");
	if (ViewLocation != -1)
	{
		glUniform3fv(ViewLocation, 1, glm::value_ptr(m_CameraPos));
	}
	GLint LightDirection = glGetUniformLocation(currentShader, "directionLight.direction");
	if (LightDirection != -1)
	{
		glUniform3fv(LightDirection, 1, glm::value_ptr(m_LightDirection));
	}
	GLint AmbientColour = glGetUniformLocation(currentShader, "directionLight.ambientColour");
	if (AmbientColour != -1)
	{
		glUniform4fv(AmbientColour, 1, glm::value_ptr(m_AmbientLightColour));
	}
	GLint DiffuseColour = glGetUniformLocation(currentShader, "directionLight.diffuseColour");
	if (DiffuseColour != -1)
	{
		glUniform4fv(DiffuseColour, 1, glm::value_ptr(m_DiffuseLightColour));
	}
	GLint SpecularColour = glGetUniformLocation(currentShader, "directionLight.specularColour");
	if (SpecularColour != -1)
	{
		glUniform4fv(SpecularColour, 1, glm::value_ptr(m_SpecularLightColour));
	}

	m_TeaPot->OnRender(m_ViewMatrix, m_ProjMatrix);
}

void MyGame::update()
{



	GameApplication::update();
	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(m_CameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	/*mat4 translation = translate(mat4(1.0), vec3(0.0f, 0.0f, -1.0f));
	mat4 rotationX = rotate(mat4(1.0f), 0.5f, vec3(1.0f, 0.0f, 0.0f));
	mat4 rotationY = rotate(mat4(1.0f), 0.5f, vec3(0.0f, 1.0f, 0.0f));
	mat4 rotationZ = rotate(mat4(1.0f), 0.5f, vec3(0.0f, 0.0f, 1.0f));
	mat4 rotationAll = rotationX * rotationY * rotationZ;*/
	//m_TestObject->OnUpdate();
	m_TeaPot->OnUpdate();



}

void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_LEFT)
	{
		m_CameraPos.x -= 0.1f;
	}
}
