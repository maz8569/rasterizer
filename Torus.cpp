#include "Torus.h"

Torus::Torus(size_t radial_resolution, size_t tubular_resolution, float radius, float thickness)
{
    float Su = 1.0f, Sv = 1.0f;

    for (size_t i = 0; i < radial_resolution; i++) {
        for (size_t j = 0; j < tubular_resolution; j++) {
            float u = (float)j / tubular_resolution * M_PI * 2.0;
            float v = (float)i / radial_resolution * M_PI * 2.0;
            float x = (radius + thickness * std::cos(v)) * std::cos(u);
            float y = (radius + thickness * std::cos(v)) * std::sin(u);
            float z = thickness * std::sin(v);

            float tx = u / (2 * M_PI);
            float ty = v / (2 * M_PI);
            
            /*
            u = 0.0f;
            if (pos.y != 0) {
                u = Su / (2 * M_PI) * atanf(pos.z / pos.y) - 0.5f;
            }
            v = Sv / M_PI * tan(pos.y / pos.length()) - 0.5f;
            */
            vertices.push_back(Vertex({ x, y, z }, { 0, 0, 0 }, {tx, ty, 0}));
        }
    }

    for (size_t i = 0; i < radial_resolution; i++) {
        auto i_next = (i + 1) % radial_resolution;
        for (size_t j = 0; j < tubular_resolution; j++) {
            uint16_t j_next = (j + 1) % tubular_resolution;
            uint16_t i0 = i * tubular_resolution + j;
            uint16_t i1 = i * tubular_resolution + j_next;
            uint16_t i2 = i_next * tubular_resolution + j_next;
            uint16_t i3 = i_next * tubular_resolution + j;
            indices.push_back({ i0, i2, i1 });
            indices.push_back({ i2, i0, i3 });
        }
    }
    makeNormals();
}
