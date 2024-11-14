#ifndef SLOT_HPP
#define SLOT_HPP

#include <cstdint>
#include <string>
#include "slot_type.hpp"

struct slot
{
    int32_t id;
    slot_type type;
    std::string name;
};



#endif
