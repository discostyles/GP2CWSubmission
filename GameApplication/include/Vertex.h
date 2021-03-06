#ifndef VERTEX_H
#define VERTEX_H
#include "Common.h"

struct Vertex
{
	vec3 position;
	vec4 colour;
	vec2 texCoord;
	vec3 normals;
	vec3 tangent;
	vec3 binormal;
};

#endif

