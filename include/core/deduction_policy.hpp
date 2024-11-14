#ifndef DEDUCTION_POLICY_HPP
#define DEDUCTION_POLICY_HPP

#include <map>
#include <vector>
#include <cstdint>

#include "deduction_type.hpp"
#include "slot_type.hpp"

class DeductionPolicy
{
private:

    deduction_type mode;
    slot_type defaultType;

    std::map<slot_type, int32_t> typePriority;

    slot_type deduceStrictType(const std::vector<slot_type>& first, const std::vector<slot_type>& scecond) const;

    slot_type deduceCoerciveType(const std::vector<slot_type>& first, const std::vector<slot_type>& second) const;

    slot_type deduceGenericFallbackType(const std::vector<slot_type>& first, const std::vector<slot_type>& second) const;

    slot_type deduceCustomPriorityType(const std::vector<slot_type>& first, const std::vector<slot_type>& second) const;

public:

    DeductionPolicy();

    slot_type deduceType(const std::vector<slot_type> &first, const std::vector<slot_type> &second) const;

    void setMode(const deduction_type & mode);

    void setDefaultType(const slot_type &type);

    const slot_type &getDefaultType() const;

};

#endif
