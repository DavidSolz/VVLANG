#ifndef NODE_DRAFT_HPP
#define NODE_DRAFT_HPP

#include "slot.hpp"
#include "node_type.hpp"

struct node_draft
{
    std::string name;
    node_type type;
    int32_t numInput;
    int32_t numOutput;
    slot * input;
    slot * output;
};

#endif
