#pragma once

#include "TSPSolverParams.hpp"
#include "Path.hpp"
#include "Result.hpp"
#include "Opt.hpp"

class TSPSolver {
private:
    const TSPSolverParams params;

    Path generate_random_path() const noexcept;
    long double calculate_distance(const Path&, const Combination&) const noexcept;
    tuple<Combination, long double, bool> get_miminal_combination(const Path& path, Opt* opt) const noexcept;
    Path opt2(Path) const noexcept;
    Path opt3(Path) const noexcept;
    Solution solve(Path, Path(TSPSolver::*)(Path) const noexcept, const char* algorithm_name) const noexcept;
public:
    TSPSolver(const TSPSolverParams&) noexcept;
    Result solve() const noexcept;
};