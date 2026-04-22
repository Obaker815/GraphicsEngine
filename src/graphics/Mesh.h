#pragma once
#include <vector>

#include "Vertex.h"

struct Mesh{
    Vertex* verticies;

    float x, y = 0;
    float width, height;
    float rotation;

    Texture* texture;

    Mat4 getTransform() const
    {
        return Mat4::scale(width, height) *
               Mat4::rotateZ(-rotation) *
               Mat4::translate(x, y);
    }
};
