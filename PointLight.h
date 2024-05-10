#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(float3 position, float3 ambient, float3 diffuse, float3 specular, float shininess, Texture* texture);
	virtual float3 calculate(Fragment& frag, VertexProcessor& vp);
};

