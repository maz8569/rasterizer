#pragma once
#include <string>
#include "vector3.h"

class Texture
{

	int width, height, channels;

public:
	uint3* color;

	Texture();
	Texture(std::string filePath);
	~Texture();

	void cleanUp();
	uint3 getPixel(int x, int y);
	float3 getPixel(float x, float y);
	unsigned int calculateIndex(int x, int y) const;
};

