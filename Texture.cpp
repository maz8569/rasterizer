#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define M_PI 3.14159265358979323846
#include "ext.h"
Texture::Texture()
{
}

Texture::Texture(std::string filePath)
{
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
	
	const int size = width * height;
	color = new uint3[size];
	if (data) {
		for (int i = 0, j = 0; j < size; i += channels, ++j)
		{
			switch (channels)
			{
			case 3:
				color[j] = uint3(static_cast<int>(data[i]), static_cast<int>(data[i + 1]), static_cast<int>(data[i + 2]));
				break;
			default:
				break;
			}
		}
	}


	stbi_image_free(data);
}

Texture::~Texture()
{
	//cleanUp();
}

void Texture::cleanUp()
{
	delete[] color;
}

uint3 Texture::getPixel(int x, int y)
{
	return color[calculateIndex(x, y)];
}

float3 Texture::getPixel(float u, float v)
{
	u = u * width;
	int ui = (int)u;   // works if u is positive

	v = v * height;
	int vi = (int)v;

	if (ui < 0) {
		ui += width;
	}

	if (vi < 0) {
		vi += height;
	}

	uint3 temp = color[clamp(abs(ui), 0, width) + clamp(abs(vi), 0, height) * (width)];
	return float3(temp.x, temp.y, temp.z);
}

unsigned int Texture::calculateIndex(int x, int y) const
{
	return y + x;
}
