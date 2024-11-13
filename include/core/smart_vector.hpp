#ifndef SMARTVECTOR_H
#define SMARTVECTOR_H

#include "guid.hpp"

#include <memory>
#include <cstring>
#include <stdexcept>

template <class TYPE>
class SmartVector {
public:
    SmartVector(int32_t initialSize = 16);
    ~SmartVector();

    // Only one of those two will be left at the end - depending if the simplicity or the safety is what is more important
    virtual GUID add(TYPE*& newElement);
    virtual GUID add(std::unique_ptr<TYPE>& newElement);

    virtual void remove(GUID id);
    virtual void removeAll();

    TYPE* get(GUID id) const;
    TYPE** getAll() const;
    int32_t getElementCount() const;
    bool IDValid(GUID id) const;

    std::unique_ptr<TYPE> getOwnership(GUID id);

protected:
    TYPE** elements; // indexed by internal ID - main data storage
    int32_t* elementsID; // indexed by internal ID - map of internal ID to GUID
    int32_t elementsUsed;
    int32_t elementsAllocated;

    int32_t* IDMap; // indexed by GUID - map of GUID to internal ID
    int32_t IDMapUsed;
    int32_t IDMapAllocated;

    virtual void resizeElements(int32_t increment);
    void resizeMap(int32_t increment);

    void checkIfIDValid(GUID id) const;
};

template <class TYPE>
SmartVector<TYPE>::SmartVector(int32_t initialSize) {
    elementsAllocated = initialSize;
    elementsUsed = 0;
    elements = new TYPE*[elementsAllocated];
    elementsID = new int32_t[elementsAllocated];

    IDMapAllocated = initialSize;
    IDMapUsed = 0;
    IDMap = new int32_t[IDMapAllocated];

}

template <class TYPE>
SmartVector<TYPE>::~SmartVector(){
    for (int32_t i = 0; i < elementsUsed; i++){
        delete elements[i];
    }

    delete[] elements;
    delete[] elementsID;
    delete[] IDMap;
}

template <class TYPE>
void SmartVector<TYPE>::resizeElements(int32_t increment){
    elementsAllocated += increment;
    TYPE** newElements = new TYPE*[elementsAllocated];
    int32_t* newElementsID = new int32_t[elementsAllocated];

    std::memcpy(newElements, elements, elementsUsed * sizeof(TYPE*));
    std::memcpy(newElementsID, elementsID, elementsUsed * sizeof(int32_t));

    delete[] elements;
    delete[] elementsID;

    elements = newElements;
    elementsID = newElementsID;
}

template <class TYPE>
void SmartVector<TYPE>::resizeMap(int32_t increment){
    IDMapAllocated += increment;
    int32_t* newIDMap = new int32_t[IDMapAllocated];

    std::memcpy(newIDMap, IDMap, IDMapUsed * sizeof(int32_t));

    delete[] IDMap;

    IDMap = newIDMap;
}

template <class TYPE>
GUID SmartVector<TYPE>::add(TYPE*& newElement){
    elements[elementsUsed] = newElement;
    newElement = nullptr;

    IDMap[IDMapUsed] = elementsUsed;
    elementsID[elementsUsed] = IDMapUsed;

    elementsUsed++;
    if (elementsUsed == elementsAllocated){
        resizeElements(elementsAllocated);
    }

    IDMapUsed++;
    if (IDMapUsed == IDMapAllocated){
        resizeMap(elementsAllocated);
    }

    return GUID(IDMapUsed-1);
}

template <class TYPE>
GUID SmartVector<TYPE>::add(std::unique_ptr<TYPE>& newElement){
    elements[elementsUsed] = newElement.release();

    IDMap[IDMapUsed] = elementsUsed;
    elementsID[elementsUsed] = IDMapUsed;

    elementsUsed++;
    if (elementsUsed == elementsAllocated){
        resizeElements(elementsAllocated);
    }

    IDMapUsed++;
    if (IDMapUsed == IDMapAllocated){
        resizeMap(elementsAllocated);
    }

    return GUID(IDMapUsed-1);
}

template <class TYPE>
void SmartVector<TYPE>::remove(GUID id){
    checkIfIDValid(id);

    int32_t elementPosition = IDMap[id];
    IDMap[id] = -1;

    delete elements[elementPosition];

    elementsUsed--;
    elements[elementPosition] = elements[elementsUsed];
    IDMap[elementsID[elementsUsed]] = elementPosition;
    elementsID[elementPosition] = elementsID[elementsUsed];
}

template <class TYPE>
void SmartVector<TYPE>::removeAll(){
    for (int32_t i = 0; i < elementsUsed; i++){
        delete elements[i];
    }
    elementsUsed = 0;

    delete[] IDMap;
    IDMapUsed = 0;
    IDMapAllocated = 16;
    IDMap = new int32_t[IDMapAllocated];
}

template<class TYPE>
int32_t SmartVector<TYPE>::getElementCount() const {
    return elementsUsed;
}

template<class TYPE>
TYPE** SmartVector<TYPE>::getAll() const {
    return elements;
}

template <class TYPE>
TYPE* SmartVector<TYPE>::get(GUID id) const {
    checkIfIDValid(id);

    return elements[IDMap[id]];
}

template <class TYPE>
bool SmartVector<TYPE>::IDValid(GUID id) const {
    if (id >= IDMapUsed){
        return false;
    }
    return IDMap[id] >= 0;
}

template <class TYPE>
void SmartVector<TYPE>::checkIfIDValid(GUID id) const {
    if (IDValid(id) == false){
        throw std::invalid_argument("id is not valid");
    }
}

template <class TYPE>
std::unique_ptr<TYPE> SmartVector<TYPE>::getOwnership(GUID id){
    checkIfIDValid(id);

    int32_t elementPosition = IDMap[id];
    IDMap[id] = -1;

    std::unique_ptr<TYPE> out(elements[elementPosition]);

    elementsUsed--;
    elements[elementPosition] = elements[elementsUsed];
    IDMap[elementsID[elementsUsed]] = elementPosition;
    elementsID[elementPosition] = elementsID[elementsUsed];

    return out;
}

#endif
