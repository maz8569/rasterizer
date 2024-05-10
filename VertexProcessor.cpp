#include "VertexProcessor.h"

void VertexProcessor::calculateFinalMatrix()
{

	objrot = obj2world;
	objrot[3] = { 0, 0, 0, 0 };

	obj2proj = obj2world * world2view;

	obj2proj = obj2proj * view2proj;

}

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= M_PI / 360;
	float f = cos(fovy) / sin(fovy);
	view2proj[0] = { f / aspect, 0, 0, 0 };
	view2proj[1] = { 0, f, 0, 0 };
	view2proj[2] = { 0, 0, (far + near) / (near - far), -1 };
	view2proj[3] = { 0, 0, 2 * far * near / (near - far), 0 };
	calculateFinalMatrix();
}

void VertexProcessor::setLookAt(const float3 eye, float3 center, float3 up)
{
	float3 f = center - eye;
	f = f.getNormalized();
	up = up.normalize();
	viewDir = -f;
	float3 s = f.crossProduct(up);
	//s.normalize();
	float3 u = s.crossProduct(f);
	//u.normalize();
	/*
	world2view[0] = {s[0], s[1], s[2], -eye[0]};
	world2view[1] = {u[0], u[1], u[2], -eye[1]};
	world2view[2] = {-f[0], -f[1], -f[2], -eye[2]};
	world2view[3] = {0, 0, 0, 1};
	*/

	world2view[0] = { s[0], u[0], -f[0], 0 };
	world2view[1] = { s[1], u[1], -f[1], 0 };
	world2view[2] = { s[2], u[2], -f[2], 0 };
	world2view[3] = { 0, 0, 0, 1 };

	float4x4 m;
	m[3] = { -eye[0], -eye[1], -eye[2], 1 };

	world2view = m * world2view;
	//world2view.transpose();



	calculateFinalMatrix();

	//std::cout << "\n" << obj2proj << "\n";

}

void VertexProcessor::setModel(float4x4& modelMatrix)
{
	obj2world = modelMatrix;
	calculateFinalMatrix();
}

float3 VertexProcessor::tr(const float3 vertex)
{

	float4 res = obj2proj * vertex;

	return {res.x / res.w, res.y / res.w, res.z / res.w };
}
