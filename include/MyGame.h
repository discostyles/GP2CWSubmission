#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void initScene();
	void destroyScene();
	void render();
	void update();

	//GLuint m_ShaderProgram;
	/*GLuint m_Texture;
	GLuint m_Sampler;*/

	// matrices
	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;
	//mat4 m_ModelMatrix;
	
	float m_RotationX;

	void onKeyDown(SDL_Keycode keyCode);	

private:
	/*GLuint m_VBO;
	GLuint m_VAO;*/
<<<<<<< HEAD

	GLuint m_DepthFBO;

	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	GLuint depthMap;

=======
>>>>>>> origin/master
	GameObject* m_TestObject;
	GameObject* m_TeaPot;
	vec3 m_CameraPos;

	vector<shared_ptr<GameObject> > m_GameObjectList;

	vec3 m_LightDirection;
	vec4 m_AmbientLightColour;
	vec4 m_DiffuseLightColour;
	vec4 m_SpecularLightColour;
};
#endif
