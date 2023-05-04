#include "i_object.hpp"

IObject::IObject()
{
}

IObject::~IObject()
{
}

uint8_t IObject::getPriority() const
{
    return priority_;
}
