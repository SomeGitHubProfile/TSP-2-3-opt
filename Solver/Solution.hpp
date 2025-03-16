#pragma once

#include <string>
#include <chrono>

#include "json.hpp"

#include "Path.hpp"

using namespace std;
using json = nlohmann::json;

struct Solution {
    Path path;
    chrono::nanoseconds time;
    string algorithm_name;

    json to_json() const noexcept {
        return json{
            {"path", path.to_json()},
            {"time", time.count()},
            {"algorithm_name", algorithm_name}
        };
    }
};