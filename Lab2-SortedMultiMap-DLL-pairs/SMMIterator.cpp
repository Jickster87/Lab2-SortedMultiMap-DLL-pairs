#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    currentElement = map.head;
}

void SMMIterator::first(){
    currentElement = map.head;
}

void SMMIterator::next(){
    if (!valid()) {
        throw exception();
    }
    currentElement = currentElement->next;
}

bool SMMIterator::valid() const{
    return currentElement != nullptr;
}

TElem SMMIterator::getCurrent() const{
    if (!valid()) {
        throw exception();
    }
    return currentElement->elems;
}


