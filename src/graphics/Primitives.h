#pragma once
#include <vector>

struct Vertex {
    float x, y, z;
    float u, v;
};

namespace Primitives
{
    std::vector<Vertex> Triangle(
        float x1, float y1, float u1, float v1,
        float x2, float y2, float u2, float v2,
        float x3, float y3, float u3, float v3
    );

    std::vector<Vertex> Quad(
        float x, float y, float w, float h,
        float u0, float v0,
        float u1, float v1
    );
}
