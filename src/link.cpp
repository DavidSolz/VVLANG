#include "core/link.hpp"

uint64_t link::hash() const
{
    uint64_t state = from.parent * 747796405u + 2891336453u;
    uint64_t word = ((state >> ((from.child >> 28u) + to.parent)) ^ to.child) * 277803737u;
    return (word >>22u) ^ word;
}
