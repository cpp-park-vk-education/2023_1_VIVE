#pragma once

#include <string>

#include "message.hpp"

class ISerializible {
public:
    virtual std::string serialize(const Message& msg) = 0;
    virtual Message deserialize(std::string msgStr) = 0;
};


class Serializer : public ISerializible {
    std::string serialize(const Message& msg) override;
    Message deserialize(std::string msgStr) override;
};
