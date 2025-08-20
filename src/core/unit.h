#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace uray {
class Component;

class Unit
{
public:
    Unit(const std::string& name = "Unit");
    ~Unit();

    void Update();

    void AddComponent(Component* component);

    const std::string& GetName() const { return _name; }
    void SetName(const std::string& name) { _name = name; }

    const glm::vec3& GetPosition() const { return _position; }
    void SetPosition(const glm::vec3& position)
    {
        _position = position;
        UpdateModelMatrix();
    }
    const glm::vec3& GetRotation() const { return _rotation; }
    void SetRotation(const glm::vec3& rotation)
    {
        _rotation = rotation;
        UpdateModelMatrix();
    }
    const glm::vec3& GetScale() const { return _scale; }
    void SetScale(const glm::vec3& scale)
    {
        _scale = scale;
        UpdateModelMatrix();
    }

    void UpdateModelMatrix();
    const glm::mat4& GetModelMatrix() const { return _modelMatrix; }

private:
    std::vector<Component*> _components;

    std::string _name;

    glm::vec3 _position = glm::vec3(0.0f);
    glm::vec3 _rotation = glm::vec3(0.0f);
    glm::vec3 _scale = glm::vec3(1.0f);

    glm::mat4 _modelMatrix = glm::mat4(1.0f);
};
} // namespace uray