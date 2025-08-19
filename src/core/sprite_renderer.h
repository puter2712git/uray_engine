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

private:
    unsigned char* _img;
    GLuint _texture;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
};
} // namespace uray