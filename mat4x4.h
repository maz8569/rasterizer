#pragma once
#include <iostream>
#include <iomanip>
#include "float4.h"
#include "vector3.h"
#define M_PI 3.14159265358979323846

class float4x4 {

    float4 x[4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
public:
    float4x4() {}
    float4x4(float4x4& old){
        x[0] = old.x[0];
        x[1] = old.x[1];
        x[2] = old.x[2];
        x[3] = old.x[3];
    }

    float4x4(float a, float b, float c, float d, float e, float f, float g, float h,
        float i, float j, float k, float l, float m, float n, float o, float p)
    {
        x[0][0] = a;
        x[0][1] = b;
        x[0][2] = c;
        x[0][3] = d;

        x[1][0] = e;
        x[1][1] = f;
        x[1][2] = g;
        x[1][3] = h;

        x[2][0] = i;
        x[2][1] = j;
        x[2][2] = k;
        x[2][3] = l;

        x[3][0] = m;
        x[3][1] = n;
        x[3][2] = o;
        x[3][3] = p;
    }

    //const float* operator [] (uint8_t i) const { return x[i]; }
    //float* operator [] (uint8_t i) { return x[i]; }
    float4& operator[] (uint8_t i)
    {
        return (x)[i];
    }

    float get(uint8_t i)
    {
        if (i > 15 || i < 0)
            return NULL;

        return x[i / 4][i % 4];
    }

    float4x4& indentity() {
        float4x4 m;
        return m;
    }

    float4x4& translate(float3 v) {
        float4x4 m;
        //m[0] = {1, 0, 0, v.x};
        //m[1] = {0, 1, 0, v.y};
        //m[2] = {0, 0, 1, v.z};
        m[3] = {v.x, v.y, v.z, 1};

        m = *this * m;

        return m;
    }

    float4x4& scale(float3 v) {
        float4x4 m;
        m[0] = { v.x, 0, 0, 0 };
        m[1] = { 0, v.y, 0, 0 };
        m[2] = { 0, 0, v.z, 0 };

        m = *this * m;


        return m;
    }

    float4x4& rotate(float a, float3 v) {
        float s = sin(a * M_PI / 180), c = cos(a * M_PI / 180);
        v = v.normalize();
        float4x4 m;
        m[0] = { v.x * v.x * (1 - c) + c, v.y * v.x * (1 - c) + v.z * s, v.x * v.z * (1 - c) - v.y * s, 0 };
        m[1] = { v.x * v.y * (1 - c) - v.z * s, v.y * v.y * (1 - c) + c, v.y * v.z * (1 - c) - v.x * s, 0 };
        m[2] = { v.x * v.z * (1 - c) + v.y * s, v.y * v.z * (1 - c) - v.x * s, v.z * v.z * (1 - c) + c, 0 };
        
        m = *this * m;

        return m;
    }

    float4x4& transposed() {

        float4x4 m( x[0][0],
                    x[1][0],
                    x[2][0],
                    x[3][0],

                    x[0][1],
                    x[1][1],
                    x[2][1],
                    x[3][1],

                    x[0][2],
                    x[1][2],
                    x[2][2],
                    x[3][2],

                    x[0][3],
                    x[1][3],
                    x[2][3],
                    x[3][3]);


        return m;
    }

    float4x4& transpose() {
        *this = transposed();
        return *this;
    }
    
    float4x4& operator * (float4x4& v)
    {
        float4x4 tmp;
        multiply(*this, v, tmp);

        return tmp;
    }

    float4x4& operator *= (float4x4& v)
    {
        float4x4 tmp;
        multiply(*this, v, tmp);

        *this = tmp;

        return *this;
    }

    float4& operator* (float3 v) 
    {
        float a, b, c, w;
        a = v[0] * x[0][0] + v[1] * x[1][0] + v[2] * x[2][0] + x[3][0];
        b = v[0] * x[0][1] + v[1] * x[1][1] + v[2] * x[2][1] + x[3][1];
        c = v[0] * x[0][2] + v[1] * x[1][2] + v[2] * x[2][2] + x[3][2];
        w = v[0] * x[0][3] + v[1] * x[1][3] + v[2] * x[2][3] + x[3][3];

        float4 result = { a , b , c, w }; //?? dla oswietlenia
        return result;
    }
    //float4& operator* (const float4& v);

    static void multiply(const float4x4& a, const float4x4& b, float4x4& c) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                c.x[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    c.x[i][j] += a.x[i][k] * b.x[k][j];
                }
            }
        }
    }

    friend std::ostream& operator << (std::ostream& s, const float4x4& m)
    {
        std::ios_base::fmtflags oldFlags = s.flags();
        int width = 12; // total with of the displayed number
        s.precision(5); // control the number of displayed decimals
        s.setf(std::ios_base::fixed);

        s << "[" << std::setw(width) << m.x[0][0] <<
            " " << std::setw(width) << m.x[0][1] <<
            " " << std::setw(width) << m.x[0][2] <<
            " " << std::setw(width) << m.x[0][3] << "\n" <<

            " " << std::setw(width) << m.x[1][0] <<
            " " << std::setw(width) << m.x[1][1] <<
            " " << std::setw(width) << m.x[1][2] <<
            " " << std::setw(width) << m.x[1][3] << "\n" <<

            " " << std::setw(width) << m.x[2][0] <<
            " " << std::setw(width) << m.x[2][1] <<
            " " << std::setw(width) << m.x[2][2] <<
            " " << std::setw(width) << m.x[2][3] << "\n" <<

            " " << std::setw(width) << m.x[3][0] <<
            " " << std::setw(width) << m.x[3][1] <<
            " " << std::setw(width) << m.x[3][2] <<
            " " << std::setw(width) << m.x[3][3] << "]";

        s.flags(oldFlags);
        return s;
    }

};