#include "Target.h"
#include <iostream>


TGABuffer::TGABuffer(unsigned int width, unsigned int height)
{
	SetSize(width, height);
}

void TGABuffer::Save(std::string name)
{
	name += ".tga";
	unsigned short header[9] = {
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0100, 0x0100, // width and height
		0x0820 };

	FILE* f;
	fopen_s(&f, name.c_str(), "wb+");
	if (NULL == f) return;

	header[6] = width;
	header[7] = height;

	fwrite(header, 2, 9, f);
	fwrite(colorBuffer, 4, width * height, f);

}

void TGABuffer::SetSize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	ClearBuffer();

	colorBuffer = new unsigned int[width * height];
	depthBuffer = new float[width * height];
}

void TGABuffer::ClearColor(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int color = GetColorFromRGB(r, g, b);
	for (unsigned int i = 0; i < width * height; i++)
	{
		colorBuffer[i] = color;
	}
}

void TGABuffer::ClearDepth()
{
	for (unsigned int i = 0; i < width * height; i++)
	{
		depthBuffer[i] = clearDepth;
	}
}

void TGABuffer::ClearBuffer()
{
	delete[] colorBuffer;
	delete[] depthBuffer;
}

void TGABuffer::AddTriangle(
	Vertex v1, Vertex v2, Vertex v3,
	VertexProcessor& processor, Light& light, bool isPhong)
{

	float3 pos1 = processor.tr(v1.position);
	float3 pos2 = processor.tr(v2.position);
	float3 pos3 = processor.tr(v3.position);

	float x1 = (pos1.x + 1) * width * 0.5f;
	float y1 = (pos1.y + 1) * height * 0.5f;
	float x2 = (pos2.x + 1) * width * 0.5f;
	float y2 = (pos2.y + 1) * height * 0.5f;
	float x3 = (pos3.x + 1) * width * 0.5f;
	float y3 = (pos3.y + 1) * height * 0.5f;

	float z1 = (pos1.z + 1) * clearDepth * 0.5f;
	float z2 = (pos2.z + 1) * clearDepth * 0.5f;
	float z3 = (pos3.z + 1) * clearDepth * 0.5f;

	float3 c1, c2, c3;

	if (!isPhong) {
		c1 = light.calculate(v1, processor);
		c2 = light.calculate(v2, processor);
		c3 = light.calculate(v3, processor);
	}

	float minX = std::max(std::min(std::min(x1, x2), x3), 0.0f);
	float maxX = std::min(std::max(std::max(x1, x2), x3), width - 1.0f);
	float minY = std::max(std::min(std::min(y1, y2), y3), 0.0f);
	float maxY = std::min(std::max(std::max(y1, y2), y3), height - 1.0f);

	float dx12 = x1 - x2;
	float dx23 = x2 - x3;
	float dx31 = x3 - x1;

	float dy12 = y1 - y2;
	float dy23 = y2 - y3;
	float dy31 = y3 - y1;

	float div = 1 / (-dy23 * dx31 + dx23 * dy31);

	float l1 = 0;
	float l2 = 0;
	float l3 = 0;

	bool tl1 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
	bool tl2 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
	bool tl3 = (dy31 < 0 || (dy31 == 0 && dx31 > 0));
	
	bool s1;
	bool s2;
	bool s3;

	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {

			if (tl1) {
				s1 = (((dx12) * (y - y1) - (dy12) * (x - x1)) >= 0);
			}
			else {
				s1 = (((dx12) * (y - y1) - (dy12) * (x - x1)) > 0);
			}

			if (tl2) {
				s2 = (((dx23) * (y - y2) - (dy23) * (x - x2)) >= 0);
			}
			else {
				s2 = (((dx23) * (y - y2) - (dy23) * (x - x2)) > 0);
			}

			if (tl3) {
				s3 = (((dx31) * (y - y3) - (dy31) * (x - x3)) >= 0);
			}
			else {
				s3 = (((dx31) * (y - y3) - (dy31) * (x - x3)) > 0);
			}

			if (s1 && s2 && s3) {
				l1 = (dy23 * (x - x3) - dx23 * (y - y3)) * div;
				l2 = (dy31 * (x - x3) - dx31 * (y - y3)) * div;
				l3 = 1 - l1 - l2;

				float depth = l1 * z1 + l2 * z2 + l3 * z3;
				int index = y * width + x;

				if (depth > depthBuffer[index]) {
					if (isPhong) {
						float3 pos = l1 * v1.position + l2 * v2.position + l3 * v3.position;
						float3 norm = l1 * v1.normal + l2 * v2.normal + l3 * v3.normal;
						float3 uv = l1 * v1.uv + l2 * v2.uv + l3 * v3.uv;
						Fragment frag(pos, norm.normalize(), uv);
						c1 = light.calculate(frag, processor);
						colorBuffer[index] = GetColorFromRGB(c1.r, c1.g, c1.b);
					}
					else {
						colorBuffer[index] = GetColorFromRGB(l1 * c1.r, l1 * c1.g, l1 * c1.b) + GetColorFromRGB(l2 * c2.r, l2 * c2.g, l2 * c2.b) + GetColorFromRGB(l3 * c3.r, l3 * c3.g, l3 * c3.b);
					}
					depthBuffer[index] = depth;
				}



				//colorBuffer[y * width + x] = l1 * 0xffff0000 ;
			}
		}
	}

}

unsigned int TGABuffer::GetColorFromRGB(unsigned int r, unsigned int g, unsigned int b)
{
	return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

unsigned int* TGABuffer::getColorBuffer()
{
	return colorBuffer;
}
