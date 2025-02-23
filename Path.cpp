#include "Path.h"

Path::Path() noexcept : size(0), length(0), vertices(nullptr) {}

Path::Path(size_t _size, long double _length) noexcept : size(_size), length(_length) {
    vertices = new size_t[size];
}

Path::Path(const Path& rhs) : size(rhs.size), length(rhs.length) {
    vertices = new size_t[size];
    for (size_t i = 0; i < size; ++i) {
        vertices[i] = rhs.vertices[i];
    }
}

Path& Path::operator=(const Path& rhs) {
    if (this == &rhs) {
        return *this;
    }
    if (vertices) {
        delete[] vertices;
    }
    size = rhs.size;
    length = rhs.length;
    vertices = new size_t[size];
    for (size_t i = 0; i < size; ++i) {
        vertices[i] = rhs.vertices[i];
    }
    return *this;
}

Path::~Path() {
    if (vertices) {
        delete[] vertices;
    }
}