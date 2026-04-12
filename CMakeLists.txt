cmake_minimum_required(VERSION 3.16)
project(GraphicsEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(GraphicsEngine src/main.cpp)

target_link_libraries(GraphicsEngine
    OpenGL::GL
    glfw
    GLEW::GLEW
)
