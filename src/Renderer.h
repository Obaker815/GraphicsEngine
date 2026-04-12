#pragma once

#include <vector>
#include "Primitives.h"
#include <glad/glad.h>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void submit(const std::vector<Vertex>& vertices);
    void flush();

private:
    std::vector<Vertex> batch;

    unsigned int VAO;
    unsigned int VBO;
};
