#include "Camera.h"

Camera::Camera()
{
	m_CameraPos = vec3(0.0f, 0.0f, 1.0f);
	m_LookatPos = vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = vec3(0.0f, 0.0f, 0.0f);
	m_MinBounds = vec3(0.0f, 0.0f, 0.0f);
	m_MaxBounds = vec3(0.0f, 0.0f, 0.0f);
	colliding = false;
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
		//m_CameraPos.x -= 0.1f;
		//m_LookatPos.x -= 0.1f;
	}
	if (keyCode == SDLK_RIGHT)
	{
		//m_CameraPos.x += 0.1f;
		//m_LookatPos.x += 0.1f;
	}
	if (keyCode == SDLK_UP || keyCode == SDLK_w)
	{
		GameApplication game;
		game.CollisionDetected((vec3(m_CameraPos.x + 0.3f * cos(m_Rotation.y), m_CameraPos.y, m_CameraPos.z + 0.3f*sin(m_Rotation.y))) - 0.5f,
			(vec3(m_CameraPos.x + 0.3f * cos(m_Rotation.y), m_CameraPos.y, m_CameraPos.z + 0.3f*sin(m_Rotation.y)) + 0.5f));
		if (!colliding)
		{
			m_CameraPos.z += 0.3f * sin(m_Rotation.y);
			m_CameraPos.x += 0.3f * cos(m_Rotation.y);
			m_MinBounds = m_CameraPos - 0.5f;
			m_MaxBounds = m_CameraPos + 0.5f;
		}
	}
	if (keyCode == SDLK_DOWN || keyCode == SDLK_s)
	{
		GameApplication game;
		game.CollisionDetected((vec3(m_CameraPos.x - 0.3f * cos(m_Rotation.y), m_CameraPos.y, m_CameraPos.z - 0.3f*sin(m_Rotation.y))) - 0.5f,
			(vec3(m_CameraPos.x - 0.3f * cos(m_Rotation.y), m_CameraPos.y, m_CameraPos.z - 0.3f*sin(m_Rotation.y)) + 0.5f));
		if (!colliding)
		{
			m_CameraPos.z -= 0.3f * sin(m_Rotation.y);
			m_CameraPos.x -= 0.3f * cos(m_Rotation.y);
			m_MinBounds = m_CameraPos - 0.5f;
			m_MaxBounds = m_CameraPos + 0.5f;
		}
	}
	if (keyCode == SDLK_a)
	{
		m_Rotation.y -= radians(1.0f);
		if(m_Rotation.y > radians(360.0f))
		{
			m_Rotation.y -= radians(360.0f);
		}
		if (m_Rotation.y < radians(0.0f))
		{
			m_Rotation.y += radians(360.0f);
		}
		m_LookatPos.x = cos(m_Rotation.y);
		m_LookatPos.z = sin(m_Rotation.y);
	}
	if (keyCode == SDLK_d)
	{
		m_Rotation.y += radians(1.0f);
		if (m_Rotation.y > radians(360.0f))
		{
			m_Rotation.y -= radians(360.0f);
		}
		if (m_Rotation.y < radians(0.0f))
		{
			m_Rotation.y += radians(360.0f);
		}
		m_LookatPos.x = cos(m_Rotation.y);
		m_LookatPos.z = sin(m_Rotation.y);
	}
}

void Camera::SetBool(bool collision)
{
	colliding = collision;
}
