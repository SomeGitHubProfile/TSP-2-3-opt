#pragma once

#include <string>
#include <unordered_map>

#include "Coords.hpp"

using namespace std;

enum class Modes {
    Path,
    Cycle
};

static const unordered_map<string, Modes> modes_strings{
    {"Path", Modes::Path},
    {"Cycle", Modes::Cycle}
};

static const size_t number_of_modes = modes_strings.size();

struct TSPSolverParams {
    Modes mode;
    size_t number_of_vertices;
    Coords* vertices;
    size_t k; // 1 means comparison mode

    TSPSolverParams() noexcept;
    TSPSolverParams(const TSPSolverParams&) noexcept;
    void delete_vertices() noexcept;
    ~TSPSolverParams();
};