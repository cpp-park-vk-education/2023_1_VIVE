#pragma once

#include "item.hpp"

#include <vector>

class Inventory
{
protected:
    std::vector<Item> items_;
    std::vector<Item> weapons_;
    int curr_weapon_;

public:
    Inventory();
    virtual ~Inventory();
};
