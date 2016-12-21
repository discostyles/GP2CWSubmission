#include "GameObject.h"

GameObject::GameObject()
{
	m_VBO = 0;
	m_VAO = 0;
	m_IBO = 0;
	/*m_FBO = 0;
	m_DBO = 0;*/
	m_ShaderProgram = 0;
	m_DiffuseTexture = 0;
	//m_RenderedTexture = 0;
	m_Sampler = 0;
	m_SpeclarTex = 0;
	m_NormalTexture = 0;
	m_HeightMap = 0;

	m_ModelMatrix = mat4(1.0f);
	m_TranslationMatrix = mat4(1.0f);
	m_RotationMatrix = mat4(1.0f);
	m_ScaleMatrix = mat4(1.0f);

	m_Position = vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = vec3(0.0f, 0.0f, 0.0f);
	m_Scale = vec3(1.0f, 1.0f, 1.0f);
	m_MinBounds = vec3(0.0f, 0.0f, 0.0f);
	m_MaxBounds = vec3(0.0f, 0.0f, 0.0f);
	m_NumberOfVerts = 0;
	m_NumberOfIndices = 0;

	m_AmbientMaterialColour = vec4(0.1f, 0.1f, 0.1f, 1.0f);
	m_DiffuseMaterialColour = vec4(0.8f, 0.0f, 0.0f, 1.0f);
	m_SpecularMaterialColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularPower = 25.0f;
}

GameObject::~GameObject()
{

}

void GameObject::OnUpdate()
{
	m_RotationMatrix = eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_ScaleMatrix = scale(m_Scale);
	m_TranslationMatrix = translate(m_Position);

	m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
}

void GameObject::OnRender(mat4 & view, mat4 & projection)
{
	//glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);
	


	GLint ModelLocation = glGetUniformLocation(m_ShaderProgram, "Model");
	if (ModelLocation != -1)
	{
		glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
	}

	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram, "MVP");
	if (MVPLocation != -1)
	{
		mat4 MVP = projection*view*m_ModelMatrix;
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	}

	GLint AmbientColour = glGetUniformLocation(m_ShaderProgram, "ambientMaterialColour");
	if (AmbientColour != -1)
	{
		glUniform4fv(AmbientColour, 1, glm::value_ptr(m_AmbientMaterialColour));
	}

	GLint DiffuseColour = glGetUniformLocation(m_ShaderProgram, "diffuseMaterialColour");
	if (DiffuseColour != -1)
	{
		glUniform4fv(DiffuseColour, 1, glm::value_ptr(m_DiffuseMaterialColour));
	}

	GLint SpecularColour = glGetUniformLocation(m_ShaderProgram, "specularMaterialColour");
	if (SpecularColour != -1)
	{
		glUniform4fv(SpecularColour, 1, glm::value_ptr(m_SpecularMaterialColour));
	}

	GLfloat SpecularPower = glGetUniformLocation(m_ShaderProgram, "specularPower");
	if (SpecularPower != -1)
	{
		glUniform1f(SpecularPower, m_SpecularPower);
	}

	GLint textureLocation = glGetUniformLocation(m_ShaderProgram, "diffuseSampler");
	glBindSampler(0, m_Sampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);

	if (textureLocation != -1)
	{
		glUniform1i(textureLocation, 0);
	}

	GLint speclarLocation = glGetUniformLocation(m_ShaderProgram, "speclarSampler");
	glBindSampler(1, m_Sampler);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_SpeclarTex);

	if (speclarLocation != -1)
	{
		glUniform1i(speclarLocation, 1);
	}

	GLint normalLocation = glGetUniformLocation(m_ShaderProgram, "normalSampler");
	glBindSampler(2, m_Sampler);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_NormalTexture);

	if (normalLocation != -1)
	{
		glUniform1i(normalLocation, 2);
	}

	GLint heightMapLocation = glGetUniformLocation(m_ShaderProgram, "heightMap");
	glBindSampler(3, m_Sampler);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_HeightMap);

	if (heightMapLocation != -1)
	{
		glUniform1i(heightMapLocation, 3);
	}

	//// Craig McLaren
	//GLint uniformTexture = glGetUniformLocation(m_ShaderProgram, "fboTexture");
	//glBindSampler(4, m_Sampler);
	//glActiveTexture(GL_TEXTURE4);
	//glBindTexture(GL_TEXTURE_2D, m_RenderedTexture);
	//if (uniformTexture != -1)
	//{
	//	glUniform1i(uniformTexture, 4);
	//}
	

	//glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVerts);
	glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_INT, 0);
	

	//generate a FBO
	/*glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	glBindTexture(GL_TEXTURE_2D, m_RenderedTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenRenderbuffers(1, &m_DBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DBO);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_RenderedTexture, 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glViewport(0, 0, 1024, 768);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1024, 768);*/

	
}

//Craig McLaren
void GameObject::OnInit()
{
	/*glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_RenderedTexture);
	glBindTexture(GL_TEXTURE_2D, m_RenderedTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 768, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
*/
	/*glGenRenderbuffers(1, &m_DBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 1024, 768);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);*/

	/*glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderedTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DBO);*/
	/*GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		fprintf(stderr, "glCheckFrameBufferStatus: error %p", status);
		return 0;
	}*/
	

}

void GameObject::OnDestroy()
{
	glDeleteProgram(m_ShaderProgram);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteRenderbuffers(1, &m_DBO);
	glDeleteTextures(1, &m_RenderedTexture);
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteTextures(1, &m_DiffuseTexture);
	glDeleteSamplers(1, &m_Sampler);
	//glDeleteFramebuffers(1, &framebuffer);
}

void GameObject::LoadDiffuseTexture(const string & filename)
{
	m_DiffuseTexture = loadTextureFromFile(filename);

	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
	glGenerateMipmap(GL_TEXTURE_2D);

	//setup sampler
	glGenSamplers(1, &m_Sampler);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_RenderedTexture);
	glBindTexture(GL_TEXTURE_2D, m_RenderedTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 768, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameObject::LoadSpeclarTexture(const string & filename)
{
	m_SpeclarTex = loadTextureFromFile(filename);

	glBindTexture(GL_TEXTURE_2D, m_SpeclarTex);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GameObject::LoadNormalTexture(const string & filename)
{
	m_NormalTexture = loadTextureFromFile(filename);

	glBindTexture(GL_TEXTURE_2D, m_NormalTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GameObject::LoadHeightTexture(const string & filename)
{
	m_HeightMap = loadTextureFromFile(filename);

	glBindTexture(GL_TEXTURE_2D, m_HeightMap);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GameObject::LoadShaders(const string & vsFilename, const string & fsFilename)
{
	GLuint vertexShaderProgram = 0;
	vertexShaderProgram = loadShaderFromFile(vsFilename, VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = loadShaderFromFile(fsFilename, FRAGMENT_SHADER);


	// create program and link above assets to program
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);
	logShaderInfo(m_ShaderProgram);
	// delete shader objects
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

// Craig McLaren
vec3 GameObject::GetMinBounds()
{
	return m_MinBounds + m_Position;
}

// Craig McLaren
vec3 GameObject::GetMaxBounds()
{
	return m_MaxBounds + m_Position;
}

void GameObject::SetObjectPosition(const vec3 & position)
{
	m_Position = position;
}

void GameObject::CopyVertexData(Vertex *pVertex, unsigned int* indices, int numberOfVertices, int numberOfIndices)
{
	m_NumberOfVerts = numberOfVertices;
	m_NumberOfIndices = numberOfIndices;
	CalculateBoundingBox(pVertex, numberOfVertices);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(Vertex), pVertex, GL_STATIC_DRAW);
	//generate a IBO
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	/*glGenRenderbuffers(1, &m_DBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 1024, 768);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderedTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DBO);*/
	
	//generate a VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	/*glBindRenderbuffer(GL_RENDERBUFFER, m_DBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);*/

	
		

	//define layout of vertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, colour));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, normals));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, tangent));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, binormal));

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Craig McLaren
void GameObject::CalculateBoundingBox(Vertex *pVertex, int numberOfVertices)
{
	m_MinBounds.x = pVertex[0].position.x;
	m_MinBounds.y = pVertex[0].position.y;
	m_MinBounds.z = pVertex[0].position.z;
	m_MaxBounds.x = pVertex[0].position.x;
	m_MaxBounds.y = pVertex[0].position.y;
	m_MaxBounds.z = pVertex[0].position.z;
	for (int i = 1; i < numberOfVertices; i++)
	{
		if (pVertex[i].position.x < m_MinBounds.x)
		{
			m_MinBounds.x = pVertex[i].position.x;
		}
		if (pVertex[i].position.x > m_MaxBounds.x)
		{
			m_MaxBounds.x = pVertex[i].position.x;
		}
		if (pVertex[i].position.y < m_MinBounds.y)
		{
			m_MinBounds.y = pVertex[i].position.y;
		}
		if (pVertex[i].position.y > m_MaxBounds.y)
		{
			m_MaxBounds.y = pVertex[i].position.y;
		}
		if (pVertex[i].position.z < m_MinBounds.z)
		{
			m_MinBounds.z = pVertex[i].position.z;
		}
		if (pVertex[i].position.z > m_MaxBounds.z)
		{
			m_MaxBounds.z = pVertex[i].position.z;
		}
	}
}

