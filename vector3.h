#pragma once
#include <iostream>

template<typename T>
struct vector3
{
    union {
        struct { T x, y, z; };
        struct { T r, g, b; };
    };

    vector3() : x(T(0)), y(T(0)), z(T(0)) {}
    vector3(T xx) : x(xx), y(xx), z(xx) {}
    vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
    vector3 operator + (const vector3& v) const
    {
        return vector3(x + v.x, y + v.y, z + v.z);
    }

    vector3 operator += (const vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }

    vector3 operator - (const vector3& v) const
    {
        return vector3(x - v.x, y - v.y, z - v.z);
    }

    vector3 operator -= (const vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    vector3 operator - () const
    {
        return vector3(-x, -y, -z);
    }
    vector3 operator * (const T& r) const
    {
        return vector3(x * r, y * r, z * r);
    }
    vector3 operator * (const vector3& v) const
    {
        return vector3(x * v.x, y * v.y, z * v.z);
    }
    T dotProduct(const vector3<T>& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    T ndotProduct(const vector3<T>& v) const
    {
        vector3 temp = this->getNormalized();
        vector3 temp2 = v.getNormalized();
        return temp.x * temp2.x + temp.y * temp2.y + temp.z * temp2.z;
    }
    vector3& operator /= (const T& r)
    {
        x /= r, y /= r, z /= r; return *this;
    }
    vector3& operator *= (const T& r)
    {
        x *= r, y *= r, z *= r; return *this;
    }
    vector3 crossProduct(const vector3<T>& v) const
    {
        return vector3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
    T norm() const
    {
        return x * x + y * y + z * z;
    }
    T length() const
    {
        return sqrt(norm());
    }

    const T& operator [] (uint8_t i) const { return (&x)[i]; }
    T& operator [] (uint8_t i) { return (&x)[i]; }
    vector3& normalize()
    {
        T n = norm();
        if (n > 0) {
            T factor = 1 / sqrt(n);
            x *= factor, y *= factor, z *= factor;
        }

        return *this;
    }

    vector3& getNormalized() const
    {
        vector3 result = *this;
        T n = result.norm();
        if (n > 0) {
            T factor = 1 / sqrt(n);
            result.x *= factor, result.y *= factor, result.z *= factor;
        }

        return result;
    }

    static vector3 reflect(const vector3& vec, const vector3& normal) {
        float dot = vec.dotProduct(normal);
        return vec - normal * (dot * 2.0f);
    }

    friend vector3 operator * (const T& r, const vector3& v)
    {
        return vector3<T>(v.x * r, v.y * r, v.z * r);
    }
    friend vector3<T> operator / (const T& r, const vector3<T>& v)
    {
        return vector3<T>(r / v.x, r / v.y, r / v.z);
    }
    friend std::ostream& operator << (std::ostream& s, const vector3<T>& v) 
    {
        return s << '[' << v.x << ' ' << v.y << ' ' << v.z << ']';
    }
};

typedef vector3<float> float3;
typedef vector3<int> int3;
typedef vector3<unsigned int> uint3;

