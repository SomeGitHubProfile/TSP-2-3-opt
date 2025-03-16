#include "Result.hpp"

Result::Result() noexcept {}

Result::Result(size_t number_of_solutions) noexcept : solutions(number_of_solutions) {}

Result::Result(const Path& _initial_path, size_t number_of_solutions) noexcept : initial_path(_initial_path), solutions(number_of_solutions) {}

Result::Result(vector<Solution> _solutions) noexcept : solutions(_solutions) {}

Result::Result(const Path& _initial_path, vector<Solution> _solutions) noexcept : initial_path(_initial_path), solutions(_solutions) {}