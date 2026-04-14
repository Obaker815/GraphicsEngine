#pragma once

#include <string>
#include <glad/glad.h>

class Shader {
public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use();

    // Set datatypes
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setMat4(const std::string& name, const float* data);

private:
    std::string loadFile(const std::string& path);
    unsigned int compileShader(unsigned int type, const std::string& source);
};
