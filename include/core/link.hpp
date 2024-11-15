#ifndef LINK_HPP
#define LINK_HPP


#include "id_pair.hpp"

struct link
{
    id_pair from;
    id_pair to;

    uint64_t hash() const;

};

#endif
