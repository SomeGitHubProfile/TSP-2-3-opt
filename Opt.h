#pragma once

#include <vector>

#include "Edge.h"

using namespace std;

struct Combination {
    vector<Edge> edges;
    vector<Edge> segments_to_reverse;
};

class Opt {
public:
    vector<Edge> edges;
    Combination initial_combination;
    vector<Combination> combinations;

    Opt() noexcept;
    Opt(vector<Edge> _edges) noexcept;
};

class Opt2 : public Opt {
public:
    Opt2(vector<Edge> edges) noexcept;
};

class Opt3 : public Opt {
public:
    Opt3(vector<Edge> edges) noexcept;
};