#pragma once

#include <memory>

class IObject;

using IObjectShPtr = std::shared_ptr<IObject>;

class IObject {
    virtual unsigned int getPriority() const = 0;
    virtual void update();
    virtual void render();

private:
    unsigned int priority_;
};
