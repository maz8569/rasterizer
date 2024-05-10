#include "Sphere.h"
#include "ext.h"

Sphere::Sphere(size_t horiz, size_t vert, float radius, float height)
{
	
	size_t vSize = vert * (horiz + 2);
	size_t tSize = vert * horiz * 2 ;

	indices = std::vector<uint3>(tSize, {0, 0, 0});
	vertices = std::vector<Vertex>(vSize, Vertex({0, 0, 0}, {0, 0, 0}));

	for (size_t yy = 0; yy <= horiz + 1; ++yy) {
		float y = cos(yy * M_PI / (horiz + 1.f));
		float r = sqrt(1 - y * y);
		for (size_t rr = 0; rr < vert; ++rr) {
			float x = r * cos(2 * M_PI * rr / vert);
			float z = r * sin(2 * M_PI * rr / vert);
			if (abs(x) < EPS) x = 0;
			if (abs(z) < EPS) z = 0;

			float Su = 1.0f, Sv = 1.0f;

			float3 pos = { x , y , z  };
			
			float u = x/2 -0.5f;
			float v = y/2 -0.5f;
			
			/*
			float u = 1.0f;
			if (y != 0) {
				u = (Su / (2.0f * M_PI)) * atan(pos.z / pos.y) -0.5f;

			}
			float v = (Sv / M_PI) * tan(pos.y / pos.length()) -0.5f;
			*/
			
			//float v = 1 - Sv * float(yy) / float(horiz);
			//float u = Su *float(rr) / float(vert - 1 );

			//float u = 0.5 + atan2(pos.z, pos.x) / (2 * M_PI);
			//float v = -0.5 + asin(pos.y) / M_PI;

			pos = pos * radius;

			vertices [rr + yy * vert ] = Vertex(pos, { 0, 0, 0 }, {u, -v, 0});
		}
	}

	uint16_t index;

	for (size_t yy = 0; yy < horiz; ++yy) {
		for (size_t rr = 0; rr < vert; ++rr) {
//			if (rr == vert / 2)
//				continue;
			index = rr + 2 * yy * vert;
			indices[index] = {

				(uint16_t)((rr + 1) % vert + yy * vert) ,
				(uint16_t)(rr + vert + yy * vert) ,
				(uint16_t)((rr + 1) % vert + vert + yy * vert)
			
			};

			index += vert;

			indices[index] = {

				(uint16_t)(rr + vert + yy * vert) ,
				(uint16_t)(rr + 2 * vert + yy * vert) ,
				(uint16_t)((rr + 1) % vert + vert + yy * vert)

			};

		}
	}

	makeNormals();
}
