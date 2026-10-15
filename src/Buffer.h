// **********************************
//
// **********************************
#pragma once
#include <cstddef>

class Buffer {
private:
    size_t size_{0};
    int* data_{nullptr};

public:
    Buffer() = default;
    Buffer(size_t n);
    ~Buffer();

    int& operator[](size_t inex);
    const int& operator[](size_t inex) const;
};

