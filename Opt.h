#pragma once

#include "Edge.h"

using namespace std;

class Opt {
public:
    Combination initial_combination;
    vector<Combination> combinations; // edges must be written according to their order

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