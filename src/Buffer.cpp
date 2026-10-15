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

// copy CTor
Buffer::Buffer(const Buffer &other)
    : size_(other.size_), data_(new int[other.size_])
{
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = other.data_[i];
    }
}

// ----------------------------------
// Destructor
// ----------------------------------
Buffer::~Buffer() { delete[] data_; }

// ----------------------------------
// operators
// ----------------------------------

int &Buffer::operator[](size_t i)
{
    assert(i < size_ && "Index out of bounds");
    return data_[i];
}

const int &Buffer::operator[](size_t i) const
{
    assert(i < size_ && "Index out of bounds");
    return data_[i];
}

size_t Buffer::size() const { return size_; }
