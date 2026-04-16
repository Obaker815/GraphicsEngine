#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Renderer.h"
#include "Vertex.h"
#include "Texture.h"
#include "Sprite.h"

#include "MathUtils.h"
#include "Camera.h"
#include "Deltatime.h"

#include "KeybindManager.h"
#include "Keybind.h"

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
    Camera camera(
            windowSize[0] / 10.0f, 
            windowSize[1] / 10.0f);

    // init a sprite
    Texture texture;

    Sprite sprite;
    sprite.x = 40.0f;
    sprite.y = 40.0f;
    sprite.width  = 24.0f;
    sprite.height = 10.0f;
    sprite.rotation = 0.0f;

    // full texture
    sprite.u0 = 0.0f;
    sprite.v0 = 0.0f;
    sprite.u1 = 1.0f;
    sprite.v1 = 1.0f;

    sprite.texture = &texture;

    KeybindManager keybindManager;

    Keybind closeKey;
    closeKey.key = GLFW_KEY_ESCAPE;
    closeKey.onPress = [window]() {
            glfwSetWindowShouldClose(window, true); 
            std::cout << "Escape key pressed, exiting\n"; 
    };
    keybindManager.AddKeybind(&closeKey);

    Keybind rightKey;
    rightKey.key = GLFW_KEY_RIGHT;
    rightKey.onPress = [&sprite]() {
        sprite.x += 1.0f * Deltatime::dt;
    };
    keybindManager.AddKeybind(&rightKey);

    Deltatime::reset();

    while (!glfwWindowShouldClose(window))
    {
        Deltatime::update();

        keybindManager.Update(window);
        sprite.rotation = Deltatime::elapsedTime();

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
