#pragma once
#include "vector3.h"

struct Vertex
{
	float3 position;
	float3 normal;
	float3 uv;

	Vertex(float3 Position, float3 Normal);
	Vertex(float3 Position, float3 Normal, float3 UV);
};

typedef Vertex Fragment;