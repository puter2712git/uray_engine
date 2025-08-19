#include "unit.h"

#include <glm/gtc/matrix_transform.hpp>

namespace uray {
Unit::Unit(const std::string& name)
    : _name(name)
{
}

Unit::~Unit() {}

void Unit::UpdateModelMatrix()
{
    _modelMatrix = glm::translate(glm::mat4(1.0f), _position) *
                   glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0)) *
                   glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0, 1, 0)) *
                   glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0, 0, 1)) *
                   glm::scale(glm::mat4(1.0f), _scale);
}
} // namespace uray