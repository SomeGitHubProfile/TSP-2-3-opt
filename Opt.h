#pragma once

#include <vector>

#include "Edge.h"

using namespace std;

typedef vector<Edge> Combination;

class Opt {
public:
    Combination initial_combination;
    vector<Combination> combinations;

    Opt() noexcept;
    Opt(const Combination&) noexcept;
};

class Opt2 : public Opt {
public:
    Opt2(const Combination&) noexcept;
};

class Opt3 : public Opt {
public:
    Opt3(const Combination&) noexcept;
};