#pragma once
#include "Math.h"

class Camera
{
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    float width;
    float height;

    Camera(float w, float h)
        : width(w), height(h) {}

    Mat4 getProjection() const
    {
        return Mat4::ortho(0.0f, width, height, 0.0f);
    }

    Mat4 getView() const
    {
        return Mat4::translate(-x, -y, -z);
    }

    Mat4 getVP() const
    {
        return getProjection() * getView();
    }
};
