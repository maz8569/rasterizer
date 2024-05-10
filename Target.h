#pragma once
#include <string>
#include "vector3.h"
#include "Light.h"
#include "VertexProcessor.h"

class TGABuffer
{

	unsigned int width;
	unsigned int height;
	float clearDepth = -100.f;


	unsigned int* colorBuffer;
	float* depthBuffer;

public:

	TGABuffer(unsigned int width, unsigned int height);

	void Save(std::string name);

	void SetSize(unsigned int width, unsigned int height);

	void ClearColor(unsigned int r, unsigned int g, unsigned int b);

	void ClearDepth();

	void ClearBuffer();

	void AddTriangle(	Vertex v1, Vertex v2, Vertex v3,
						VertexProcessor& processor, Light& light, bool isPhong);

	unsigned int GetColorFromRGB(unsigned int r, unsigned int g, unsigned int b);

	unsigned int* getColorBuffer();

};

