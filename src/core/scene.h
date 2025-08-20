#pragma once

#include <string>
#include <vector>

namespace uray {
class Unit;

class Scene
{
public:
    Scene(const std::string& name = "NewScene");
    ~Scene();

    void Update();

    void AddUnit(Unit* unit);

private:
    std::string _name;

    std::vector<Unit*> _units;
};
} // namespace uray