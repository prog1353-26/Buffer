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
    Buffer(const Buffer& other);         // copy-ctor
    Buffer( Buffer&& other) noexcept;    // move-ctor

    ~Buffer();

    Buffer& operator=(const Buffer& other);  // copy
    Buffer& operator=(Buffer&& other);       // move

    int& operator[](size_t inex);
    const int& operator[](size_t inex) const;
    size_t size() const;
};

