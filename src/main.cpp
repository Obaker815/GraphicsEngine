#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Renderer.h"
#include "Primitives.h"
#include "Texture.h"
#include "Sprite.h"
#include "Math.h"
#include "Camera.h"
#include "Stopwatch.h"

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    int windowSize[2] = {1920, 1080};

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowSize[0], windowSize[1], "GraphicsEngine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    // GLAD init (must be after context)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    glViewport(0, 0, windowSize[0], windowSize[1]);

    Shader shader("../shaders/basic.vert", "../shaders/basic.frag");
    Renderer renderer;
    Camera camera(windowSize[0], windowSize[1]);

    // init a sprite
    Texture texture;

    Sprite sprite;
    sprite.x = 400.0f;
    sprite.y = 400.0f;
    sprite.width  = 4.0f * 194.0f;
    sprite.height = 4.0f * 108.0f;
    sprite.rotation = 0.0f;

    // full texture
    sprite.u0 = 0.0f;
    sprite.v0 = 0.0f;
    sprite.u1 = 1.0f;
    sprite.v1 = 1.0f;

    sprite.texture = &texture;

    Stopwatch timer;
    float last;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        { 
            glfwSetWindowShouldClose(window, true); 
            std::cout << "Escape key pressed, exiting\n"; 
        }

        float elapsedTime = timer.elapsed();
        float dt = elapsedTime - last;
        last = elapsedTime;

        sprite.rotation = elapsedTime;

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        renderer.drawSprite(sprite, shader);
        shader.setMat4("uVP", camera.getVP().m);
        shader.setInt("uTexture", 0);

        renderer.flush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
