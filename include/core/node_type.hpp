#ifndef NODE_TYPE_HPP
#define NODE_TYPE_HPP

#define NODE_TYPE_STR {"constant", "operator", "function"}

enum node_type
{
    CONSTANT,
    OPERATOR,
    FUNCTION,

    NUM_NODE_TYPES
};

#endif
