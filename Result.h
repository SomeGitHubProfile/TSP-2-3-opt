#pragma once

#include <chrono>

#include "Path.h"

struct Result {
    Path initial_path;
    Path path;
    std::chrono::nanoseconds time;
};