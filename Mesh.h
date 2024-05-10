#pragma once
#include <vector>
#include "vector3.h"
#include "Target.h"
#include "VertexProcessor.h"
#include "Vertex.h"
#include "Light.h"

constexpr auto EPS = 0.0001f;
class Mesh
{
protected:

	std::vector<Vertex> vertices;
	std::vector<uint3> indices;

public:

	virtual void Draw(TGABuffer& target, VertexProcessor& processor, Light& light, bool isPhong = false);
	void makeNormals();
};

