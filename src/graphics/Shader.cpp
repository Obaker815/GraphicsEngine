#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    // read the vertex and fragment shaders from their files
    std::string vertexCode = loadFile(vertexPath);
    std::string fragmentCode = loadFile(fragmentPath);

    // compile the shaders and store their IDs
    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // create the program and attach the shaders to it
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // log any errors in the shaders
    int success;
    char infoLog[512];

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
    }

    // delete the shaders as they are no longer needed CPU side
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    // use the program
    glUseProgram(ID);
}

std::string Shader::loadFile(const std::string& path)
{
    // create filestream
    std::ifstream file(path);
    std::stringstream ss;

    // read the contents of the file
    if (!file.is_open()) {
        std::cerr << "Failed to open shader: " << path << std::endl;
        return "";
    }

    // return the string
    ss << file.rdbuf();
    return ss.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    // create the shader
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();

    // use glCompileShader to compile the shader
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // log errors
    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compile error:\n" << infoLog << std::endl;
    }

    // return shader ID
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
