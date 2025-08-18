#pragma once

#include <glm/glm.hpp>

namespace uray {
class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 target = glm::vec3(0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    ~Camera();

    const glm::mat4& GetViewMatrix() const { return _viewMatrix; }
    void UpdateViewMatrix();

    const glm::vec3& GetPosition() const { return _position; }
    void SetPosition(const glm::vec3& position)
    {
        _position = position;
        _isDirty = true;
    }
    const glm::vec3& GetTarget() const { return _target; }
    void SetTarget(const glm::vec3& target)
    {
        _target = target;
        _isDirty = true;
    }

private:
    bool _isDirty = false;

    glm::vec3 _position;
    glm::vec3 _target;
    glm::vec3 _up;

    glm::mat4 _viewMatrix;
};
} // namespace uray