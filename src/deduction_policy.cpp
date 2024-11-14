#include "core/deduction_policy.hpp"

DeductionPolicy::DeductionPolicy()
{
    this->defaultType = slot_type::INTEGER;
    this->typePriority = {{slot_type::FLOAT, 3}, {slot_type::INTEGER, 2}, {slot_type::BYTE, 1}, {slot_type::STRING, 0}};
}

void DeductionPolicy::setMode(const deduction_type &mode)
{
    this->mode = mode;
}

slot_type DeductionPolicy::deduceType(const std::vector<slot_type> &first, const std::vector<slot_type> &second) const
{
    switch (mode)
    {
    case deduction_type::STRICT:
        return deduceStrictType(first, second);
    case deduction_type::COERCIVE:
        return deduceCoerciveType(first, second);
    case deduction_type::GENERIC_FALLBACK:
        return deduceGenericFallbackType(first, second);
    case deduction_type::CUSTOM_PRIORITY:
    default:
        return deduceCustomPriorityType(first, second);
    }
}

slot_type DeductionPolicy::deduceStrictType(const std::vector<slot_type> &first, const std::vector<slot_type> &scecond) const
{
    for (const auto &type : first)
    {
        if (std::find(scecond.begin(), scecond.end(), type) != scecond.end())
        {
            return type;
        }
    }
    return defaultType;
}

slot_type DeductionPolicy::deduceCoerciveType(const std::vector<slot_type> &first, const std::vector<slot_type> &second) const
{
    slot_type bestType = defaultType;
    int highestPriority = -1;

    for (const auto &typeA : first)
    {
        for (const auto &typeB : first)
        {

            if( typeA == typeB )
            {
                int32_t priority = typePriority.at(typeA);
                if (priority > highestPriority)
                {
                    bestType = typeA;
                    highestPriority = priority;
                }
            }

        }
    }

    return bestType;
}

slot_type DeductionPolicy::deduceGenericFallbackType(const std::vector<slot_type> &first, const std::vector<slot_type> &second) const
{
    slot_type commonType = deduceCoerciveType(first, second);

    if (commonType != defaultType)
    {
        return commonType;
    }

    return slot_type::GENERIC;
}

slot_type DeductionPolicy::deduceCustomPriorityType(const std::vector<slot_type> &first, const std::vector<slot_type> &second) const
{
    slot_type bestType = defaultType;
    int highestPriority = -1;

    for (const auto &typeA : first)
    {
        for (const auto &typeB : first)
        {

            if( typeA == typeB )
            {
                int32_t priority = typePriority.at(typeA);
                if (priority > highestPriority)
                {
                    bestType = typeA;
                    highestPriority = priority;
                }
            }

        }
    }
    return bestType;
}

void DeductionPolicy::setDefaultType(const slot_type &type)
{
    defaultType = type;
}

const slot_type &DeductionPolicy::getDefaultType() const
{
    return defaultType;
}
