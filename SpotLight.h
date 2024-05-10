#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
    float3 _direction;
    float _cutOff;
    float _outerCutOff;
public:
    SpotLight(  float3 position, float3 direction, float3 ambient, 
                float3 diffuse, float3 specular, float shininess, float cutOff, float outerCutOff, Texture* texture);
    virtual float3 calculate(Fragment& frag, VertexProcessor& vp);
};

