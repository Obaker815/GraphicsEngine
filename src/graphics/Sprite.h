#pragma once
#include "Texture.h"

#include "MathUtils.h"

struct Sprite
{
    float x, y;
    float width, height;
    float rotation;

    float u0, v0;
    float u1, v1;

    Texture* texture;

    Mat4 getTransform() const
    {
        return Mat4::scale(width, height) *
               Mat4::rotateZ(-rotation) *
               Mat4::translate(x, y);
    }
};
