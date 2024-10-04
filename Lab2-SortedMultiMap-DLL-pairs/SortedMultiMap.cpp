#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    head = nullptr;
    tail = nullptr;
    totalSize = 0;
    rel = r;
}

void SortedMultiMap::add(TKey c, TValue v) {
    TElem newElem = std::make_pair(c, v);
    Node * newNode = new Node(newElem);
    
    Node * nomad = head;
    while (nomad != nullptr && (rel(nomad->elems.first, c) ||  //check if sorted key OR!
          (nomad->elems.first == c && rel(nomad->elems.second, v)))) { //check if sorted value
            nomad = nomad->next;
    }
    // Insert the new node in the appropriate place
    if (nomad == head) {
        // Insert at the head
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;  // If the list was empty, also set the tail
        }
    }
    else if (nomad == nullptr) {
        // Insert at the tail
        newNode->prev = tail;
        if (tail != nullptr) {
            tail->next = newNode;
        }
        tail = newNode;
    }
    else {
        // Insert between nomad->prev and nomad
        newNode->prev = nomad->prev;
        newNode->next = nomad;
        nomad->prev->next = newNode;
        nomad->prev = newNode;
    }
    totalSize++;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    Node * nomad = head;

    // Traverse the list to find the node with key 'c' and value 'v'
    // !!! nice trick to learn
    // while not empty and negation of key is == c && value is == v, move only then
    while (nomad != nullptr && !(nomad->elems.first == c && nomad->elems.second == v)) {
        nomad = nomad->next;
    }

    // If the node is not found, return false
    if (nomad == nullptr) {
        return false;
    }

    // Case 1: Removing the head node
    if (nomad == head) {
        head = head->next;  // Move head to the next node
        if (head != nullptr) {
            head->prev = nullptr;  // Update the previous pointer of the new head
        } else {
            // If the list becomes empty after removal, also set tail to nullptr
            tail = nullptr;
        }
    }
    // Case 2: Removing the tail node
    else if (nomad == tail) {
        tail = tail->prev;  // Move tail to the previous node
        if (tail != nullptr) {
            tail->next = nullptr;  // Update the next pointer of the new tail
        }
    }
    // Case 3: Removing a node in the middle
    else {
        nomad->prev->next = nomad->next;
        nomad->next->prev = nomad->prev;
    }

    // Delete the node and reduce the size
    delete nomad;
    totalSize--;

    return true;  // Node was successfully removed
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    Node * nomad = head;
    vector<TValue> values;
    while (nomad != nullptr) {
        if (nomad->elems.first == c) {
            values.push_back(nomad->elems.second);
        }
        nomad = nomad->next;
    }
    return values;
}

int SortedMultiMap::size() const {
    return totalSize;
}

bool SortedMultiMap::isEmpty() const {
    return totalSize == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}
