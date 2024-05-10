#pragma once
#include "Light.h"

class NoLight :
    public Light
{
public:

    NoLight(Texture* texture);
    virtual float3 calculate(Fragment& frag, VertexProcessor& vp);
};

