#pragma once
#include <vector>

struct Vertex {
    float x, y, z;
};

namespace Primitives
{
    std::vector<Vertex> Triangle(
        float x1, float y1,
        float x2, float y2,
        float x3, float y3
    );

    std::vector<Vertex> Quad(
        float x, float y, float w, float h
    );
}
