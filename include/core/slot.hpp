#ifndef SLOT_HPP
#define SLOT_HPP

#include <cstdint>
#include <string>
#include "slot_type.hpp"

struct slot
{
    int32_t id;
    std::string name;
    slot_type type;
};



#endif
