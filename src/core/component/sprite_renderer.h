#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../../config.h"
#include "component.h"

namespace uray {
class SpriteRenderer : public Component
{
public:
    SpriteRenderer();
    SpriteRenderer(const std::string& imgPath);
    ~SpriteRenderer();

    void Update() override;
    void OnEnable() override;
    void OnDisable() override;

    void Render();

private:
    unsigned char* _img;
    GLuint _texture;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
};
} // namespace uray