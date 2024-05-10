#include "Cone.h"

Cone::Cone(float radius, float height, unsigned int subdivs)
{
	vertices.push_back(Vertex(float3(0.0, 0.0, 0.0), {0, 0, 0}, {0, 1, 0}));
	vertices.push_back(Vertex(float3(0.0, 0.0, height), { 0, 0, 0 }));

	for (int i = 0; i <= subdivs; i++) {

		float ratio = (float)i / subdivs;
		float r = ratio * (M_PI * 2.0);
		float x = std::cos(r) * radius;
		float z = std::sin(r) * radius;

		float u = x / 2 - 0.5f;
		float v = 0.9f;

		vertices.push_back(Vertex(float3(x, z, 0.0), { 0, 0, 0 }, {u, v, 0}));


		
		if (i > 1) {
			//indices.push_back({ (uint16_t)(vertices.size() - 1), (uint16_t)(vertices.size() - 2), 0 });
			indices.push_back({ (uint16_t)(vertices.size() - 1), (uint16_t)(vertices.size() - 2), 1 });
			indices.push_back({ (uint16_t)(vertices.size() - 2), (uint16_t)(vertices.size() - 1), 0 });
		}

	}

	//indices.push_back({ 3, (uint16_t)(vertices.size() - 1), 0 });
	indices.push_back({ 3, (uint16_t)(vertices.size() - 1), 1 });
	indices.push_back({ (uint16_t)(vertices.size() - 1), 3, 0 });
	
	makeNormals();

}
