#pragma once
#include <iostream>
struct float4
{
	union {
		struct{ float x, y, z, w; };
		struct{ float r, g, b, a; };
	};
	
	float4();
	float4(float x, float y, float z, float w);
	float4(float4& v);
	~float4();

	float length();
	float4 getNormalized();
	float4 normalize();
	static float dot(const float4& v1, const float4& v2);

	float& operator[](int i);
	const float& operator[](int i) const;
	float4& operator+=(const float4& v);
	float4& operator-=(const float4& v);
	float4& operator+(const float4& v);
	float4& operator-(const float4& v);
	float4& operator*(const float f);
	float4& operator*=(const float f);
	float4& operator/(const float f);
	float4& operator/=(const float f);
};

std::ostream& operator<<(std::ostream& strm, const float4& v);
