#include "NoLight.h"

NoLight::NoLight(Texture* texture) : Light({0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0, texture)
{
}

float3 NoLight::calculate(Fragment& frag, VertexProcessor& vp)
{
	float3 res = getTexture() != nullptr ? getTexture()->getPixel(frag.uv.x, frag.uv.y) : float3(255, 255, 255);


	return res ;// *;
}
