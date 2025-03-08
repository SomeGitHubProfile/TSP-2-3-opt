#include "Path.h"

Path::Path() noexcept : size(0), length(0), vertices(nullptr) {}

Path::Path(size_t _size, long double _length) noexcept : size(_size), length(_length) {
    vertices = new size_t[size];
}

Path::Path(const Path& rhs) noexcept : size(rhs.size), length(rhs.length) {
    vertices = new size_t[size];
    for (size_t i = 0; i < size; ++i) {
        vertices[i] = rhs.vertices[i];
    }
}


void Path::delete_vertices() noexcept {
    if (vertices) {
        delete[] vertices;
    }
    return;
}

void Path::optimize(const Combination& combination, long double distance_diff) noexcept {
    size_t* new_vertices = new size_t[size];
    size_t i = 0, j = 0;
    auto previous_edge = combination.begin();
    auto next_edge = previous_edge + 1;
    for (; i < previous_edge->from; ++i) {
        new_vertices[i] = vertices[i];
    }
    for (; next_edge != combination.end(); previous_edge = next_edge++) {
        new_vertices[i++] = vertices[previous_edge->from];
        int step = static_cast<int>(previous_edge->to < next_edge->from) * 2 - 1; // -1 if false, 1 if true
        for (j = previous_edge->to; j != next_edge->from; j += step) {
            new_vertices[i++] = vertices[j];
        }
    }
    new_vertices[i++] = vertices[previous_edge->from];
    for (j = previous_edge->to; j < size; ++j) {
        new_vertices[i++] = vertices[j];
    }
    delete_vertices();
    vertices = new_vertices;
    length -= distance_diff;
    return;
}

Path& Path::operator=(const Path& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete_vertices();
    size = rhs.size;
    length = rhs.length;
    vertices = new size_t[size];
    for (size_t i = 0; i < size; ++i) {
        vertices[i] = rhs.vertices[i];
    }
    return *this;
}

Path::~Path() {
    delete_vertices();
}