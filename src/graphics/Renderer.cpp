#include "Renderer.h"
#include "Primitives.h"
#include "Shader.h"

#include "Math.h"

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

void Renderer::drawSprite(const Sprite& sprite, Shader& shader)
{
    // Get the transform of the sprite,
    // pass it to the uModel Mat4 in the shader,
    // then bind the texture of the sprite.
    Mat4 model = sprite.getTransform();
    shader.setMat4("uModel", model.m);
    sprite.texture->bind(0);

    // Create a quad with the uvs of the sprite,
    // and submit it to the batch.
    Vertex quad[6] = {
        // Triangle 1
        {-0.5f, -0.5f, -0.5f, sprite.u0, sprite.v0}, // bottom-left
        {+0.5f, -0.5f, -0.5f, sprite.u1, sprite.v0}, // bottom-right
        {+0.5f, +0.5f, -0.5f, sprite.u1, sprite.v1}, // top-right

        // Triangle 2
        {-0.5f, -0.5f, -0.5f, sprite.u0, sprite.v0}, // bottom-left
        {+0.5f, +0.5f, -0.5f, sprite.u1, sprite.v1}, // top-right
        {-0.5f, +0.5f, -0.5f, sprite.u0, sprite.v1}  // top-left
    };
    submit(quad, 6);
}
