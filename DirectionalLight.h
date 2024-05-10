#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
private:

	float3 _direction;

public:

	DirectionalLight(float3 position, float3 direction, float3 ambient, float3 diffuse, float3 specular, float shininess, Texture* texture = nullptr);

	virtual float3 calculate(Fragment& frag, VertexProcessor& vp);
};