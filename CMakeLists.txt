cmake_minimum_required(VERSION 3.16)
project(GraphicsEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(GraphicsEngine
    src/main.cpp

    src/graphics/Texture.cpp
    src/graphics/RenderingHelper.cpp
    src/graphics/Renderer.cpp
    src/graphics/Shader.cpp

    src/engine/KeybindManager.cpp

    src/third_party/glad.c
)

target_include_directories(GraphicsEngine PRIVATE
    src
    src/core
    src/graphics
    src/third_party
    src/engine
)
target_link_libraries(GraphicsEngine
    OpenGL::GL
    glfw
)
