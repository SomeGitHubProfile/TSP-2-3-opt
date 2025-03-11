#pragma once

#include <vector>

#include "Edge.hpp"

using namespace std;

struct Path {
    long double length;
    vector<size_t> vertices;

    Path() noexcept;
    Path(size_t, long double = 0) noexcept;
    void optimize(const Combination&, long double) noexcept;
};