#pragma once

namespace uray {
class Component
{
public:
    Component();
    ~Component();

    void SetActive(bool active)
    {
        if (_isActive == active)
            return;

        _isActive = active;
        if (_isActive)
            OnEnable();
        else
            OnDisable();
    }
    bool IsActive() const { return _isActive; }

    virtual void Update() = 0;
    virtual void OnEnable() = 0;
    virtual void OnDisable() = 0;

protected:
    bool _isActive;
};
} // namespace uray