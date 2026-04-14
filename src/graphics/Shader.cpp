#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = loadFile(vertexPath);
    std::string fragmentCode = loadFile(fragmentPath);

    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    int success;
    char infoLog[512];

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

std::string Shader::loadFile(const std::string& path)
{
    std::ifstream file(path);
    std::stringstream ss;

    if (!file.is_open()) {
        std::cerr << "Failed to open shader: " << path << std::endl;
        return "";
    }

    ss << file.rdbuf();
    return ss.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compile error:\n" << infoLog << std::endl;
    }

    return shader;
}

void Shader::setInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setMat4(const std::string& name, const float* data)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, data);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}
