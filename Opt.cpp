#include "Opt.h"

Opt::Opt() noexcept : edges(0), combinations(0) {}

Opt::Opt(vector<Edge> _edges) noexcept : edges(_edges), combinations(0) {}

Opt2::Opt2(vector<Edge> edges) noexcept : Opt(edges) {
    initial_combination = {
        {{edges[0].from, edges[0].to}, {edges[1].from, edges[1].to}},
        {}
    };
    combinations = {
        {
            {{edges[0].from, edges[1].from}, {edges[0].to, edges[1].to}},
            {{edges[0].to, edges[1].to}}
        }
    };
}

Opt3::Opt3(vector<Edge> edges) noexcept : Opt(edges) {
    combinations = {
        //TODO
    };
}