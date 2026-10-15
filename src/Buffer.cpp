// **********************************
//
// **********************************
#include "Buffer.h"
#include <cassert>

// ----------------------------------
// constructors
// ----------------------------------
Buffer::Buffer(size_t n)
    : size_(n), data_(new int[n])
{
}

// ----------------------------------
// Destructor
// ----------------------------------
Buffer::~Buffer() {delete[] data_;}


// ----------------------------------
// operators
// ----------------------------------

int& Buffer::operator[](size_t i) {
    assert(i < size_ && "Index out of bounds");
    return data_[i];
}

const int& Buffer::operator[](size_t i) const {
    assert(i < size_ && "Index out of bounds");
    return data_[i];
}
