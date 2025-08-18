#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace uray {
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
    : _position(position)
    , _target(target)
    , _up(up)
{
    _viewMatrix = glm::lookAt(_position, _target, _up);
}

Camera::~Camera() {}

void Camera::UpdateViewMatrix()
{
    if (!_isDirty)
        return;

    _viewMatrix = glm::lookAt(_position, _target, _up);
}
} // namespace uray