#pragma once

#include "Params.h"
#include "Path.h"
#include "Result.h"

class TSP_Solver {
private:
    const Params params;

    Path generate_random_path() const noexcept;
    Path opt2() const noexcept;
    Path opt3() const noexcept;
public:
    TSP_Solver(const Params&) noexcept;

    Result solve() const noexcept;
};