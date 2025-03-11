#pragma once

#include <vector>

#include "Solution.hpp"

using namespace std;

struct Result {
    Path initial_path;
    vector<Solution> solutions;

    Result() noexcept;
    Result(size_t) noexcept;
    Result(const Path&, size_t) noexcept;
    Result(vector<Solution>) noexcept;
    Result(const Path&, vector<Solution>) noexcept;
};