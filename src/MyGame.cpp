#include "MyGame.h"


const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{
	m_RotationX = 0;
	m_CameraMax = vec3(0.0f, 0.0f, 0.0f);
	m_CameraMin = vec3(0.0f, 0.0f, 0.0f);
}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	GameApplication::initScene();
	//Craig McLaren
	string vShaders[] = { ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl", ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl", ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl" };
	string fShaders[] = { ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl", ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl", ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl" };
	string texPaths[] = { ASSET_PATH + TEXTURE_PATH + "/earth_diff.png", ASSET_PATH + TEXTURE_PATH + "/earth_diff.png", ASSET_PATH + TEXTURE_PATH + "/bricks_diff.jpg" };
	string specPaths[] = { ASSET_PATH + TEXTURE_PATH + "/earth_spec.png", ASSET_PATH + TEXTURE_PATH + "/earth_spec.png", ASSET_PATH + TEXTURE_PATH + "/bricks_spec.png" };
	string bumpPaths[] = { ASSET_PATH + TEXTURE_PATH + "/earth_norm.png", ASSET_PATH + TEXTURE_PATH + "/earth_norm.png", ASSET_PATH + TEXTURE_PATH + "/bricks_norm.png" };
	string heightPaths[] = { ASSET_PATH + TEXTURE_PATH + "/earth_height.png", ASSET_PATH + TEXTURE_PATH + "/earth_height.png", ASSET_PATH + TEXTURE_PATH + "/bricks_height.png" };
	string modelPaths[] = { ASSET_PATH + MODEL_PATH + "/Earth.fbx", ASSET_PATH + MODEL_PATH + "/Earth.fbx", ASSET_PATH + MODEL_PATH + "/Earth.fbx" };

	for (int i = 0; i < 3; i++)
	{
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

	m_CameraPos = camera.GetCameraPos();
	m_LookatPos = camera.GetLookatPos();
	m_LightDirection = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_DiffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	collisionsActive = true;
	colliding[0] = false;
	colliding[1] = false;
	colliding[2] = false;

	m_PostProcess = shared_ptr<PostProcessing>(new PostProcessing());
	m_PostProcess->OnInit();
}

void MyGame::destroyScene()
{
	GameApplication::destroyScene();

	m_PostProcess->Destroy();

	for (auto& go : m_GameObjectList)
	{
		go->OnDestroy();
	}
	m_GameObjectList.clear();
}

void MyGame::render()
{
	GameApplication::render();
	//m_PostProcess->Bind();
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
	//m_PostProcess->UnBind();
}

void MyGame::update()
{
	GameApplication::update();
	// Craig McLaren
	m_CameraMax = camera.GetMaxBounds();
	m_CameraMin = camera.GetMinBounds();
	m_CameraPos = camera.GetCameraPos();
	m_LookatPos = camera.GetLookatPos();
	if (collisionsActive)
	{
		CollisionDetected();
	}
	//
	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(m_CameraPos, m_LookatPos + m_CameraPos, vec3(0.0f, 1.0f, 0.0f));

	for (auto& go : m_GameObjectList)
	{
		go->OnUpdate();
	}
}

// Craig McLaren
void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	camera.OnKeyDown(keyCode);

	if (keyCode == SDLK_SPACE)
	{
		collisionsActive = !collisionsActive;
		cout << "debug toggled";
	}
}

void MyGame::CollisionDetected()
{
	// Craig McLaren
	int i = 0;
	for (auto& go : m_GameObjectList)
	{
		vec3 minBounds = go->GetMinBounds();
		vec3 maxBounds = go->GetMaxBounds();
		if ((m_CameraMin.x > minBounds.x && m_CameraMin.y > minBounds.y && m_CameraMin.z > minBounds.z) && (m_CameraMin.x < maxBounds.x && m_CameraMin.y < maxBounds.y && m_CameraMin.z < maxBounds.z))
		{
			colliding[i] = true;
		}
		else if ((m_CameraMax.x > minBounds.x && m_CameraMax.y > minBounds.y && m_CameraMax.z > minBounds.z) && (m_CameraMax.x < maxBounds.x && m_CameraMax.y < maxBounds.y && m_CameraMax.z < maxBounds.z))
		{
			colliding[i] = true;
		}
		else
		{
			colliding[i] = false;
		}
		i++;
	}
	if (colliding[0] == true || colliding[1] == true || colliding[2] == true)
	{
		camera.SetBool(true);
	}
	else
	{
		camera.SetBool(false);
	}
}
