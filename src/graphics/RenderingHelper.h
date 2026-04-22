#pragma once

#include <vector>

#include "Renderer.h"
#include "Sprite.h"
#include "Shader.h"
#include "Mesh.h"

class RenderingHelper {
public:
    RenderingHelper();
    ~RenderingHelper();

    static void drawSprite(Renderer& renderer, const Sprite& sprite, Shader& shader);
    static void drawMesh(Renderer& renderer, Mesh& mesh, Shader& shader);
};
