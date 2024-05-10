#pragma once
#include "mat4x4.h"
#include "vector3.h"
#define M_PI 3.14159265358979323846

class VertexProcessor
{
private:
public:
	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;
	float4x4 objrot;
	float4x4 obj2proj;
	float3 viewDir;


	void calculateFinalMatrix();

	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookAt(float3 eye, float3 center, float3 up);
	void setModel(float4x4& modelMatrix);
	float3 tr(const float3 vertex);

};

