#pragma once

#include <cmath>

struct Mat4
{
    float m[16];

    static Mat4 identity()
    {
        Mat4 r = {};
        r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0f;
        return r;
    }

    static Mat4 ortho(float left, float right, float bottom, float top)
    {
        Mat4 r = {};

        r.m[0] = 2.0f / (right - left);
        r.m[5] = 2.0f / (bottom - top);
        r.m[10] = -1.0f;

        r.m[12] = -(right + left) / (right - left);
        r.m[13] = -(bottom + top) / (bottom - top);
        r.m[15] = 1.0f;

        return r;
    }

    static Mat4 translate(float x, float y, float z = 0.0f)
    {
        Mat4 r = identity();
        r.m[12] = x;
        r.m[13] = y;
        r.m[14] = z;
        return r;
    }

    static Mat4 scale(float x, float y, float z = 1.0f)
    {
        Mat4 r = {};
        r.m[0] = x;
        r.m[5] = y;
        r.m[10] = z;
        r.m[15] = 1.0f;
        return r;
    }

    static Mat4 rotateZ(float angle)
    {
        Mat4 r = identity();

        float c = cos(angle);
        float s = sin(angle);

        r.m[0] = c;
        r.m[1] = s;
        r.m[4] = -s;
        r.m[5] = c;

        return r;
    }
};

inline Mat4 operator*(const Mat4& a, const Mat4& b)
{
    Mat4 r = Mat4::identity();

    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            r.m[col + row * 4] =
                a.m[0 + row * 4] * b.m[col + 0 * 4] +
                a.m[1 + row * 4] * b.m[col + 1 * 4] +
                a.m[2 + row * 4] * b.m[col + 2 * 4] +
                a.m[3 + row * 4] * b.m[col + 3 * 4];
        }
    }

    return r;
}

struct float3
{
    float x, y, z;

    float3(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z) {}
};
