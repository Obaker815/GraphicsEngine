#include "Primitives.h"

namespace Primitives
{
    std::vector<Vertex> Triangle(
        float x1, float y1, float u1, float v1,
        float x2, float y2, float u2, float v2,
        float x3, float y3, float u3, float v3
    )
    {
        return {
            {x1, y1, 0.0f, u1, v1},
            {x2, y2, 0.0f, u2, v2},
            {x3, y3, 0.0f, u3, v3}
        };
    }

    std::vector<Vertex> Quad(
        float x, float y, float w, float h,
        float u0, float v0,
        float u1, float v1
    )
    {
        float x2 = x + w;
        float y2 = y + h;

        return {
            {x,  y,  0.0f, u0, v0},
            {x2, y,  0.0f, u1, v0},
            {x2, y2, 0.0f, u1, v1},

            {x,  y,  0.0f, u0, v0},
            {x2, y2, 0.0f, u1, v1},
            {x,  y2, 0.0f, u0, v1}
        };
    }
}
