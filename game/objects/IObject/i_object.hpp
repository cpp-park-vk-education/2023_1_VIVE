#pragma once

#include <cstdint>

class IObject
{
protected:
    uint8_t priority_;

public:
    IObject();
    virtual ~IObject();

    virtual uint8_t getPriority() const;
    virtual void update() = 0;
    virtual void render() = 0;
};
