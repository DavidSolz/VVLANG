#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <cstdint>

#include "vector2.hpp"

struct node
{
    int32_t guid;
    Vector2 position;
    std::string name;
    // placeholder for input slots
    // placeholder for output slots
};

#endif