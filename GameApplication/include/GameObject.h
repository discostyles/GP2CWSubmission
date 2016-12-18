#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Texture.h"
#include "Shader.h"
#include "Vertex.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void OnUpdate();
	void OnRender(mat4& view, mat4& projection);
	void OnInit();
	void OnDestroy();

	void LoadDiffuseTexture(const string& filename);
	void LoadSpeclarTexture(const string& filename);
	void LoadNormalTexture(const string& filename);
	void LoadHeightTexture(const string& filename);
	void LoadShaders(const string& vsFilename, const string& fsFilename);

	vec3 GetMinBounds();
	vec3 GetMaxBounds();

	void SetObjectPosition(const vec3& position);

	void CopyVertexData(Vertex *pVertex, unsigned int* indices, int numberOfVertices, int numberOfIndices);

	void CalculateBoundingBox(Vertex *pVertex, int numberOfVertices);

	GLuint GetShaderProgram()
	{
		return m_ShaderProgram;
	};
	void SetAmbientMaterial(vec4& colour)
	{
		m_AmbientMaterialColour = colour;
	};

private:
	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_IBO;

	GLuint m_ShaderProgram;

	mat4 m_ModelMatrix;

	GLuint m_DiffuseTexture;
	GLuint m_Sampler;
	GLuint m_SpeclarTex;
	GLuint m_NormalTexture;
	GLuint m_HeightMap;

	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
	vec3 m_MinBounds;
	vec3 m_MaxBounds;

	vec4 m_AmbientMaterialColour;
	vec4 m_DiffuseMaterialColour;
	vec4 m_SpecularMaterialColour;
	float m_SpecularPower;

	mat4 m_TranslationMatrix;
	mat4 m_RotationMatrix;
	mat4 m_ScaleMatrix;

	int m_NumberOfVerts;
	int m_NumberOfIndices;

protected:

};

#endif



