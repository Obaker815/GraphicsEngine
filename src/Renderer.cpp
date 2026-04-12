#include "Renderer.h"

Renderer::Renderer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glEnableVertexAttribArray(0);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Renderer::submit(const std::vector<Vertex>& vertices)
{
    batch.insert(batch.end(), vertices.begin(), vertices.end());
}

void Renderer::flush()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,
        batch.size() * sizeof(Vertex),
        batch.data(),
        GL_DYNAMIC_DRAW
    );

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, batch.size());

    batch.clear();
}
