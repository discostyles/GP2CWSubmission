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

	string vShaders[] = { ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl", ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl" };
	string fShaders[] = { ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl", ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl" };
	string texPaths[] = { ASSET_PATH + TEXTURE_PATH + "/earth_diff.png", ASSET_PATH + TEXTURE_PATH + "/earth_diff.png" };
	string specPaths[] = { ASSET_PATH + TEXTURE_PATH + "/earth_spec.png", ASSET_PATH + TEXTURE_PATH + "/earth_spec.png" };
	string bumpPaths[] = { ASSET_PATH + TEXTURE_PATH + "/earth_norm.png", ASSET_PATH + TEXTURE_PATH + "/earth_norm.png" };
	string heightPaths[] = { ASSET_PATH + TEXTURE_PATH + "/earth_height.png", ASSET_PATH + TEXTURE_PATH + "/earth_height.png" };
	string modelPaths[] = { ASSET_PATH + MODEL_PATH + "/Earth.fbx", ASSET_PATH + MODEL_PATH + "/Earth.fbx" };

	for (int i = 0; i < 2; i++)
	{
		/*std::string vsPath = vShaders[i];
		std::string fsPath = fShaders[i];
		string texturePath = texPaths[i];
		string speclarPath = specPaths[i];
		string bumpPath = bumpPaths[i];
		string heightPath = heightPaths[i];
		std::string modelPath = modelPaths[i];*/

		shared_ptr<GameObject> m_TestGO = shared_ptr<GameObject>(loadModelFromFile(modelPaths[i]));
		m_TestGO->LoadShaders(vShaders[i], fShaders[i]);
		m_TestGO->LoadDiffuseTexture(texPaths[i]);
		m_TestGO->LoadSpeclarTexture(specPaths[i]);
		m_TestGO->LoadNormalTexture(bumpPaths[i]);
		m_TestGO->LoadHeightTexture(heightPaths[i]);
		m_TestGO->SetAmbientMaterial(vec4(0.1f, 0.1f, 0.1f, 1.0f));
		m_TestGO->SetObjectPosition(vec3(-5.0f + (i*10), 0.0f, 0));
		m_GameObjectList.push_back(m_TestGO);
	}

	m_CameraPos = vec3(0.0f, 0.0f, 15.0f);
	m_LightDirection = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_DiffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void MyGame::destroyScene()
{
	GameApplication::destroyScene();

	for (auto& go : m_GameObjectList)
	{
		go->OnDestroy();
	}
	m_GameObjectList.clear();

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
	for (auto& go : m_GameObjectList)
	{

		GLuint currentShader = go->GetShaderProgram();
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

		go->OnRender(m_ViewMatrix, m_ProjMatrix);
	}
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

	for (auto& go : m_GameObjectList)
	{
		go->OnUpdate();
	}
}

void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_LEFT)
	{
		m_CameraPos.x -= 0.1f;
	}
	if (keyCode == SDLK_RIGHT)
	{
		m_CameraPos.x += 0.1f;
	}
	if (keyCode == SDLK_UP)
	{
		m_CameraPos.z -= 0.1f;
	}
	if (keyCode == SDLK_DOWN)
	{
		m_CameraPos.z += 0.1f;
	}
}
