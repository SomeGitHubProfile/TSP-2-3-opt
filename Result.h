#pragma once

#include <chrono>

#include "Path.h"

struct Result {
    Path path;
    std::chrono::nanoseconds time;
};