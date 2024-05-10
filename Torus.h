#pragma once
#include "Mesh.h"

class Torus : public Mesh
{
public:
	Torus(  size_t radial_resolution,
            size_t tubular_resolution,
            float radius,
            float thickness);
};

