#pragma once

#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>

class Message
{
public:
    static constexpr size_t header_length = 4;

private:
    std::string data;
    size_t body_length;

public:
    Message() = default;
    Message(const std::string& mess);
    
    std::string getData() const;
    std::string getBody() const;
    size_t getLength() const;
};
