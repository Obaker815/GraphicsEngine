#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "RenderingHelper.h"
#include "Renderer.h"
#include "Vertex.h"
#include "Texture.h"
#include "Sprite.h"
#include "Mesh.h"

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

    Mesh mesh;
    mesh.texture = &texture;

    Vertex points[9] = {
        // Triangle 1
        {-0.5f, -0.5f, 0.0f, -0.5f, -0.5f},
        {+0.5f, -0.5f, 0.0f, +0.5f, -0.5f},
        {+0.5f, +0.5f, 0.0f, +0.5f, +0.5f},
          
        // Triangle 2
        {-0.5f, -0.5f, 0.0f, -0.5f, -0.5f},
        {+0.5f, +0.5f, 0.0f, +0.5f, +0.5f},
        {-0.5f, +0.5f, 0.0f, -0.5f, +0.5f},

        // Triangle 3
        {-1.0f, -1.0f, 0.0f, -0.5f, -0.5f},
        {+1.0f, +1.0f, 0.0f, +0.5f, +0.5f},
        {-1.0f, -1.0f, 0.0f, -0.5f, +0.5f} 
    };

    mesh.verticies = points;
    mesh.x = 40.0f;
    mesh.y = 40.0f;
    mesh.width = 10.0f;
    mesh.height = 16.0f;
    mesh.rotation = 0.0f;

    KeybindManager keybindManager;

    Keybind closeKey;
    closeKey.key = GLFW_KEY_ESCAPE;
    closeKey.onPress = [window]() {
            glfwSetWindowShouldClose(window, true); 
            std::cout << "exiting\n"; 
    };
    keybindManager.AddKeybind(&closeKey);

    Keybind rightKey;
    rightKey.key = GLFW_KEY_D;
    rightKey.active = [&mesh]() {
        mesh.x += 10.0f * Deltatime::dt;
    };
    keybindManager.AddKeybind(&rightKey);

    Deltatime::reset();

    while (!glfwWindowShouldClose(window))
    {
        Deltatime::update();
        keybindManager.Update(window);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        RenderingHelper::drawMesh(renderer, mesh, shader);
        shader.setMat4("uVP", camera.getVP().m);
        shader.setInt("uTexture", 0);

        renderer.flush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
