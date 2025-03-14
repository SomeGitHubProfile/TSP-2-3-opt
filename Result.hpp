#pragma once

#include <vector>

#include "json.hpp"

#include "Solution.hpp"

using namespace std;
using json = nlohmann::json;

struct Result {
    Path initial_path;
    vector<Solution> solutions;

    Result() noexcept;
    Result(size_t) noexcept;
    Result(const Path&, size_t) noexcept;
    Result(vector<Solution>) noexcept;
    Result(const Path&, vector<Solution>) noexcept;

    json to_json() const {
        json j;
        j["initial_path"] = initial_path.to_json();
        j["solutions"] = json::array();
        for (const auto& solution : solutions) {
            j["solutions"].push_back(solution.to_json());
        }
        return j;
    }
};