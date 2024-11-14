#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <cstdint>

#include "vector2.hpp"
#include "node_draft.hpp"

struct node
{
    int32_t id;
    Vector2 position;
    node_draft *draft;
    std::vector<slot> input;
    std::vector<slot> output;
};

#endif
