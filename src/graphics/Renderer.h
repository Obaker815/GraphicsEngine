#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Sprite.h"
#include "Vertex.h"
#include "Shader.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void drawSprite(const Sprite& sprite, Shader& shader);
    void submit(const Vertex* vertex, size_t count);
    void flush();

private:
    std::vector<Vertex> batch;

    unsigned int VAO;
    unsigned int VBO;
};
