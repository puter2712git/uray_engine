#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../config.h"

namespace uray {
class Shader
{
public:
    Shader();
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Use() const;

    void SetVec3(const std::string& name, const glm::vec3& val) const;
    void SetVec4(const std::string& name, const glm::vec4& val) const;
    void SetMat4(const std::string& name, const glm::mat4& val) const;

private:
    GLuint _program;
};
} // namespace uray