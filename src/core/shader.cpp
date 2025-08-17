#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace uray {
Shader::Shader()
{
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::ifstream vsFile(vertexPath);
    std::ifstream fsFile(fragmentPath);
    if (!vsFile.is_open()) {
        throw std::runtime_error("Failed to open vertex shader file: " + vertexPath);
    }
    if (!fsFile.is_open()) {
        throw std::runtime_error("Failed to open fragment shader file: " + fragmentPath);
    }

    std::stringstream vsBuffer;
    std::stringstream fsBuffer;
    vsBuffer << vsFile.rdbuf();
    fsBuffer << fsFile.rdbuf();

    std::string vsSourceStr = vsBuffer.str();
    std::string fsSourceStr = fsBuffer.str();
    const char* vsSource = vsSourceStr.c_str();
    const char* fsSource = fsSourceStr.c_str();

    int success;
    char infoLog[512];

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, nullptr);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSource, nullptr);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    _program = glCreateProgram();
    glAttachShader(_program, vs);
    glAttachShader(_program, fs);
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_program, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    glDeleteProgram(_program);
}

void Shader::Use() const
{
    glUseProgram(_program);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& val) const
{
    glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, &val[0]);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& val) const
{
    glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, &val[0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& val) const
{
    glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &val[0][0]);
}
} // namespace uray
