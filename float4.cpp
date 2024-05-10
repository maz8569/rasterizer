#include "float4.h"

std::ostream& operator<<(std::ostream& strm, const float4& v)
{
    return strm << "[ " << v.x << " " << v.y << " " << v.z << " " << v.a << " ]";
}

float4::float4() : x(0), y(0), z(0), w(0)
{}

float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{}

float4::float4(float4& v) : x(v.x), y(v.y), z(v.z), w(v.w)
{}

float4::~float4()
{
}

float float4::length()
{
	return (float)sqrt(pow(this->x, 2) +
		pow(this->y, 2) +
		pow(this->z, 2) +
		pow(this->w, 2));
}

float4 float4::getNormalized()
{
	float4 result = *this;
	float n = result.length();
	if (n != 0) {
		result /= n;
	}
	else {
		std::cout << "Can't divide by 0" << std::endl;
	}
	return result;
}

float4 float4::normalize()
{
	float n = this->length();
	if (n != 0) {
		*this /= n;
	}
	else {
		std::cout << "Can't divide by 0" << std::endl;
	}
	return *this;
}

float float4::dot(const float4& v1, const float4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

float& float4::operator[](int i)
{
	return (&x)[i];
}

const float& float4::operator[](int i) const
{
	return (&x)[i];

}

float4& float4::operator+=(const float4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

float4& float4::operator-=(const float4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

float4& float4::operator+(const float4& v)
{
	float4 result(x + v.x, y + v.y, z + v.z, w + v.w);
	return result;
}

float4& float4::operator-(const float4& v)
{
	float4 result(x - v.x, y - v.y, z - v.z, w - v.w);
	return result;
}

float4& float4::operator*(const float f)
{
	float4 result(x * f, y * f, z * f, w * f);
	return result;
}

float4& float4::operator*=(const float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	this->w *= f;

	return *this;
}

float4& float4::operator/(const float f)
{
	float4 result(x / f, y / f, z / f, w / f);
	return result;
}

float4& float4::operator/=(const float f)
{
	if (f != 0) {
		this->x /= f;
		this->y /= f;
		this->z /= f;
		this->w /= f;
	}
	else {
		std::cout << "Can't divide by 0" << std::endl;
	}

	return *this;
}

