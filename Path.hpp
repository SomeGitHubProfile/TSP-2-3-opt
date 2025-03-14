#pragma once

#include <vector>

#include "json.hpp"

#include "Edge.hpp"

using namespace std;
using json = nlohmann::json;

struct Path {
    long double length;
    vector<size_t> vertices;

    Path() noexcept;
    Path(size_t, long double = 0) noexcept;
    void optimize(const Combination&, long double) noexcept;

    json to_json() const {
        return json{
            {"length", length},
            {"vertices", vertices}
        };
    }
};