#pragma once

#include "Message.hpp"

class ISerializable;
using ISerializableShPtr = std::shared_ptr<ISerializable>;

class ISerializable
{
public:
    virtual ~ISerializable() {}

    virtual std::string serialize(const Message& mess) = 0;
    virtual Message deserialize(const std::string& ser_string) = 0;
};
