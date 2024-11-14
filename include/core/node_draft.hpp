#ifndef NODE_DRAFT_HPP
#define NODE_DRAFT_HPP

#include "slot.hpp"
#include "node_type.hpp"
#include <vector>

struct node_draft
{
    std::string name;
    node_type type;
    int32_t numInput;
    int32_t numOutput;
    std::vector<slot_type> possibleTypes;
    std::vector<slot> input;
    std::vector<slot> output;
};

#endif
