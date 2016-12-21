#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "Common.h"
#include "Texture.h"
#include "Shader.h"
#include "Vertex.h"

class PostProcessing 
{
public:
	PostProcessing();
	~PostProcessing();

	bool OnInit();
	void Destroy();
	void UnBind();
	void Bind();
private:
	GLuint m_FBO;
	GLuint m_Texture;
	GLuint m_RBO;
	GLuint m_Sampler;

};
#endif // !POSTPROCESSING_H

