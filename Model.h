#pragma once

#include "Params.h"
#include "Path.h"
#include "Result.h"
#include "Opt.h"

class TSP_Solver {
private:
    const Params params;

    Path generate_random_path() const noexcept;
    long double calculate_distance(const Path&, const Combination&) const noexcept;
    tuple<Combination, long double, bool> get_miminal_combination(const Path& path, Opt* opt) const noexcept;
    Path opt2() const noexcept;
    Path opt3() const noexcept;
public:
    TSP_Solver(const Params&) noexcept;

    Result solve() const noexcept;
};