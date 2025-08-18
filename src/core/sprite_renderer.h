#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../config.h"

namespace uray {
class SpriteRenderer
{
public:
    SpriteRenderer();
    SpriteRenderer(const std::string& imgPath);
    ~SpriteRenderer();

    void Render();

    const glm::mat4& GetTransform() const { return _transform; }
    void SetTransform(const glm::mat4& transform) { _transform = transform; }

private:
    unsigned char* _img;
    GLuint _texture;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;

    glm::mat4 _transform = glm::mat4(1.0f);
};
} // namespace uray