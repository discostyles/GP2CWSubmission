#ifndef _GAMEAPPLICATION_H
#define _GAMEAPPLICATION_H

#include "Common.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "ModelLoading.h"

//Game Application class, this basically wraps up the initialisation of a game
//this will be the base class of any game we are making. You should override this
//and some of the methods to create your own game
class GameApplication:public NonCopyable
{
public:
	//Constructor
	GameApplication();
	//Virtual Deconstructor
	virtual ~GameApplication();

	// function to quit
	void onQuit();

	//function to create a window
	void createWindow(const string& windowTitle, const unsigned int width, const unsigned int height, const unsigned int windowFlags = 0);

	//This is where all major subsystems are created
	virtual bool init(int args,char * arg[]);

	//Basically runs our game
	void run();

	void onBeginRender();

	void onEndRender();

	virtual void render();

	virtual void update();

	void initGraphics();

	void setViewport(int width, int height);

	virtual void initScene();

	virtual void destroyScene();

	virtual void onKeyDown(SDL_Keycode keyCode);

protected:
	ProgramOptions m_Options;
	//SDL windows
	SDL_Window * m_pWindow;
	SDL_GLContext m_GLcontext;
	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	unsigned int m_WindowCreationFlags;
	string m_WindowTitle;
	bool m_bIsRunning;
	void parseConfig(int args,char * arg[]);
};
#endif
