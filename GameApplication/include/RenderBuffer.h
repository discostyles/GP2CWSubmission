#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "Common.h"
#include "Texture.h"
#include "Shader.h"
#include "Vertex.h"

class RenderBuffer
{
public:
	RenderBuffer();
	~RenderBuffer();
	
	bool OnInit();
	void Destroy();
	void Bind();
	void UnBind();


private:
	GLuint m_RBO;

};
#endif // !RENDERBUFFER_H

