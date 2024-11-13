#ifndef GUID_H
#define GUID_H

#include <cstdint>

template <class TYPE>
class SmartVector;

struct GUID{
    template <class TYPE>
    friend class SmartVector;

    GUID();

    bool operator==(const GUID& other) const;
    void copy(const GUID& other);// you can only copy valid values
    void operator=(const GUID& other);

private:
    int32_t value;

    GUID(int32_t value);
    operator int32_t() const ;
    void set(int32_t newValue); // you can not set value by yourself to not compromise it's validity
};



GUID::GUID(): value(-1){}

GUID::GUID(int32_t value): value(value){}

bool GUID::operator==(const GUID& other) const {
    return value == other;
}

void GUID::copy(const GUID& other) {
    value = other;
}

void GUID::operator=(const GUID& other){
    copy(other);
}

GUID::operator int32_t() const {
    return value;
}

void GUID::set(int32_t newValue){
    value = newValue;
}

#endif