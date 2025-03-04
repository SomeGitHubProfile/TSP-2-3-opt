#pragma once

#include "Edge.h"

struct Path {
    size_t size;
    long double length;
    size_t* vertices;

    Path() noexcept;
    Path(size_t, long double = 0) noexcept;
    Path(const Path&);
    void delete_vertices() noexcept;
    void optimize(const Combination&, long double) noexcept;
    Path& operator=(const Path&);
    ~Path();
};