#include "Camera.h"

Camera::Camera()
{
	m_CameraPos = vec3(0.0f, 0.0f, 15.0f);
	m_LookatPos = vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
}

vec3 Camera::GetCameraPos()
{
	return m_CameraPos;
}

vec3 Camera::GetLookatPos()
{
	return m_LookatPos;
}

void Camera::OnKeyDown(SDL_Keycode keyCode)
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
