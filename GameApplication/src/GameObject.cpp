#include "GameObject.h"

GameObject::GameObject()
{
	m_VBO = 0;
	m_VAO = 0;
	m_IBO = 0;
	m_ShaderProgram = 0;
	m_DiffuseTexture = 0;
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

	if (speclarLocation != -1)
	{
		glUniform1i(normalLocation, 2);
	}

	GLint heightMapLocation = glGetUniformLocation(m_ShaderProgram, "heightMap");
	glBindSampler(3, m_Sampler);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_HeightMap);

	if (speclarLocation != -1)
	{
		glUniform1i(heightMapLocation, 3);
	}

	//glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVerts);
	glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_INT, 0);
}

void GameObject::OnInit()
{

}

void GameObject::OnDestroy()
{
	glDeleteProgram(m_ShaderProgram);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
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

void GameObject::CopyVertexData(Vertex *pVertex, unsigned int* indices, int numberOfVertices, int numberOfIndices)
{
	m_NumberOfVerts = numberOfVertices;
	m_NumberOfIndices = numberOfIndices;
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(Vertex), pVertex, GL_STATIC_DRAW);
	//generate a IBO
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	//generate a VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
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
}
