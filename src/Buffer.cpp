// **********************************
//
// **********************************
#include "Buffer.h"
#include <cassert>
#include <algorithm>

// ----------------------------------
// constructors
// ----------------------------------
Buffer::Buffer(size_t n)
    : size_(n), data_(new int[n])
{
    std::memset(data_, 0, size_ * sizeof(int));
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
// assignment operators
// ----------------------------------

// copy-assignmnet operator
Buffer& Buffer::operator=(const Buffer& other) {
    if(this != &other){
        int* tmp_data = new int[other.size_]; // new data buffer
        for(size_t i=0;i<other.size_;++i){
            tmp_data[i] = other.data_[i];
        }
        delete[] data_;
        data_ = tmp_data;
        size_ = other.size_;
    }
    return *this;
}



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
