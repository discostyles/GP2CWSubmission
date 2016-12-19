#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "GameApplication.h"

class Camera
{
public:
	Camera();
	~Camera();

	vec3 GetCameraPos();
	vec3 GetLookatPos();

	void OnKeyDown(SDL_Keycode keyCode);

	void SetBool(bool collision);
	
	vec3 GetMinBounds();
	vec3 GetMaxBounds();
	

private:
	vec3 m_CameraPos;
	vec3 m_LookatPos;
	vec3 m_Rotation;
	vec3 m_MinBounds;
	vec3 m_MaxBounds;

	bool colliding;

	

};
#endif
