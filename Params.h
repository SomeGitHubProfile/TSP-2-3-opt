#pragma once

#include <string>

#include "Coords.h"

enum class Modes {
    Path,
    Cycle
};

constexpr std::string_view modes_strings[] = {
    "Path",
    "Cycle"
};

constexpr size_t number_of_modes = std::size(modes_strings);

struct Params {
    Modes mode;
    size_t number_of_vertices;
    Coords* vertices;
    size_t k;

    Params() noexcept;
    Params(const Params& rhs);
    ~Params();
};