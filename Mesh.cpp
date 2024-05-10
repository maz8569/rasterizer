#include "Mesh.h"

void Mesh::Draw(TGABuffer& target, VertexProcessor& processor, Light& light, bool isPhong)
{
	for (int i = 0; i < indices.size(); i++) {
        target.AddTriangle(	vertices[indices[i].x],
                            vertices[indices[i].y],
                            vertices[indices[i].z],
							processor, light, isPhong);
	}
}

void Mesh::makeNormals()
{
	int i = 0;
	float3 n = { 0, 0, 0 };
	for (i = 0; i < indices.size(); ++i) {
		n = vertices[indices[i].z].position - vertices[indices[i].x].position;
		n = n.crossProduct(vertices[indices[i].y].position - vertices[indices[i].x].position);
		n.normalize();

		vertices[indices[i].x].normal += n;
		vertices[indices[i].y].normal += n;
		vertices[indices[i].z].normal += n;
	}

	for (i = 0; i < vertices.size(); ++i) {
		vertices[i].normal.normalize();
	}
}
