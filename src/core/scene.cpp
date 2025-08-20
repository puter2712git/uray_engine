#include "scene.h"

#include "unit.h"

namespace uray {
Scene::Scene(const std::string& name)
    : _name(name)
{
}

Scene::~Scene() {}

void Scene::Update()
{
    for (auto& unit : _units) {
        if (unit)
            unit->Update();
    }
}

void Scene::AddUnit(Unit* unit)
{
    _units.push_back(unit);
}
} // namespace uray