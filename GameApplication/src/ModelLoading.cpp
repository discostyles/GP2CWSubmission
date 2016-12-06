#include "ModelLoading.h"

//http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
GameObject * loadModelFromFile(const string & filename)
{
	LOG(INFO,"Attempting to load model %s",filename.c_str());
	GameObject *gameObject = new GameObject();
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	aiColor4D whiteColour(1.0f, 1.0f, 1.0f, 1.0f);
	
	const aiScene* scene = aiImportFile(filename.c_str(), aiProcess_JoinIdenticalVertices|aiProcess_Triangulate | aiProcess_FlipUVs|aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (scene)
	{
		LOG(INFO,"Parsing Model %s",filename.c_str());
		const aiMesh * mesh=scene->mMeshes[0];

		vector<unsigned int> indices;
		vector<Vertex> verts;

		for (int f = 0; f < mesh->mNumFaces; f++)
		{
			const aiFace * face = &mesh->mFaces[f];
			for (int i = 0; i < face->mNumIndices; i++)
			{
				int index = face->mIndices[i];
				indices.push_back(index);
			}
		}
		bool hasColour = false; 
		for (int v = 0; v < mesh->mNumVertices; v++)
		{
			aiVector3D position = mesh->mVertices[v];

			Vertex ourV;
			ourV.position = vec3(position.x, position.y, position.z);
			for (int currentChanel = 0; currentChanel < mesh->GetNumUVChannels(); currentChanel++)
			{
				if (mesh->mTextureCoords[currentChanel] != NULL)
				{
					aiVector3D meshTexture = mesh->mTextureCoords[currentChanel][v];
					ourV.texCoord = vec2(meshTexture.x, meshTexture.y);
				}
			}
			if (mesh->HasNormals())
			{
				aiVector3D meshNormal = mesh->mNormals[v];
				ourV.normals = vec3(meshNormal.x, meshNormal.y, meshNormal.z);
			}
			if (mesh->HasTangentsAndBitangents())
			{
				aiVector3D meshTangent = mesh->mTangents[v];
				ourV.tangent = vec3(meshTangent.x, meshTangent.y, meshTangent.z);
				aiVector3D meshBitagent = mesh->mBitangents[v];
				ourV.binormal = vec3(meshBitagent.x, meshBitagent.y, meshBitagent.z);
			}
			for (int currentColourChannel = 0; currentColourChannel < mesh->GetNumColorChannels(); currentColourChannel++)
			{
				if (mesh->mColors[currentColourChannel] != NULL)
				{
					hasColour = true;
					aiColor4D currentColour = mesh->mColors[currentColourChannel][v];
					ourV.colour = vec4(currentColour.r, currentColour.g, currentColour.b, currentColour.a);
				}
			}
			if (hasColour == false)
			{
				ourV.colour = vec4(whiteColour.r, whiteColour.g, whiteColour.b, whiteColour.a);
			}
			verts.push_back(ourV);
		}


		gameObject->CopyVertexData(&verts[0], &indices[0], verts.size(), indices.size());
	}
	else
	{
		LOG(ERROR,"Error Parsing Model %s",aiGetErrorString());
	}

	aiReleaseImport(scene);


	return gameObject;
}
