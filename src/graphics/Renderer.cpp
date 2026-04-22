#include "Renderer.h"
#include "Shader.h"

#include "MathUtils.h"

Renderer::Renderer()
{
    // Genarate the VAO and VBO,
    // then bind them.
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Renderer::submit(const Vertex* vertices, size_t count)
{
    // Insert the new verticies at the end of the batch
    batch.insert(batch.end(), vertices, vertices + count);
}

void Renderer::flush()
{
    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO and push the batch to it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        batch.size() * sizeof(Vertex),
        batch.data(),
        GL_DYNAMIC_DRAW
    );

    // Draw the triangles, then clear the batch.
    glDrawArrays(GL_TRIANGLES, 0, batch.size());
    batch.clear();
}
