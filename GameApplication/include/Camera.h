#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"

class Camera
{
public:
	Camera();
	~Camera();

	vec3 GetCameraPos();
	vec3 GetLookatPos();

	void OnKeyDown(SDL_Keycode keyCode);

private:
	vec3 m_CameraPos;
	vec3 m_LookatPos;

};
#endif
