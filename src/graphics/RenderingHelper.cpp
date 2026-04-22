#include "RenderingHelper.h"
#include "Renderer.h"
#include "Shader.h"
#include "MathUtils.h"

void RenderingHelper::drawSprite(Renderer& renderer, const Sprite& sprite, Shader& shader)
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
    renderer.submit(quad, 6);
}

void RenderingHelper::drawMesh(Renderer& renderer, Mesh& mesh, Shader& shader)
{
    // Get the transform of the sprite,
    // pass it to the uModel Mat4 in the shader,
    // then bind the texture of the sprite.
    Mat4 model = mesh.getTransform();
    shader.setMat4("uModel", model.m);
    mesh.texture->bind(0);

    // Take the verticies of the mesh 
    // then submit them to the renderer
    Vertex* verticies = mesh.verticies;
    renderer.submit(verticies, sizeof(verticies));
}
