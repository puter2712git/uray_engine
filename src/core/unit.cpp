#include "unit.h"

#include <glm/gtc/matrix_transform.hpp>

#include "component/component.h"

namespace uray {
Unit::Unit(const std::string& name)
    : _name(name)
{
}

Unit::~Unit()
{
    for (auto& component : _components)
        delete component;
    _components.clear();
}

void Unit::Update()
{
    for (auto& component : _components) {
        if (component->IsActive())
            component->Update();
    }
}

void Unit::AddComponent(Component* component)
{
    if (component)
        _components.push_back(component);
}

void Unit::UpdateModelMatrix()
{
    _modelMatrix = glm::translate(glm::mat4(1.0f), _position) *
                   glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1, 0, 0)) *
                   glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0, 1, 0)) *
                   glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0, 0, 1)) *
                   glm::scale(glm::mat4(1.0f), _scale);
}
} // namespace uray