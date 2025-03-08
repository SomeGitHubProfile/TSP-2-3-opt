#pragma once

#include <vector>
#include <string>
#include <chrono>

#include "Path.h"

using namespace std;

struct Solution {
    Path path;
    std::chrono::nanoseconds time;
    string algorithm_name;
};

struct Result {
    Path initial_path;
    vector<Solution> solutions;

    Result() noexcept;
    Result(size_t) noexcept;
    Result(const Path&, size_t) noexcept;
    Result(vector<Solution>) noexcept;
    Result(const Path&, vector<Solution>) noexcept;
};