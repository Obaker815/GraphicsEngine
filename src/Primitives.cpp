#include "Primitives.h"

namespace Primitives
{
    std::vector<Vertex> Triangle(
        float x1, float y1,
        float x2, float y2,
        float x3, float y3)
    {
        return {
            {x1, y1, 0.0f},
            {x2, y2, 0.0f},
            {x3, y3, 0.0f}
        };
    }

    std::vector<Vertex> Quad(
        float x, float y, float w, float h)
    {
        float x2 = x + w;
        float y2 = y + h;

        return {
            {x,  y,  0.0f},
            {x2, y,  0.0f},
            {x2, y2, 0.0f},

            {x,  y,  0.0f},
            {x2, y2, 0.0f},
            {x,  y2, 0.0f}
        };
    }
}
