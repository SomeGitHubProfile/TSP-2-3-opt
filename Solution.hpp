#pragma once

#include <string>
#include <chrono>

#include "Path.hpp"

using namespace std;

struct Solution {
    Path path;
    chrono::nanoseconds time;
    string algorithm_name;
};