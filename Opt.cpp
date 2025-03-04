#include "Opt.h"

Opt::Opt() noexcept : initial_combination(0), combinations(0) {}

Opt::Opt(const Combination& edges) noexcept : initial_combination(edges), combinations(0) {}

Opt2::Opt2(const Combination& edges) noexcept : Opt(edges) {
    combinations = {
        {
            {edges[0].from, edges[1].from},
            {edges[0].to, edges[1].to}
        }
    };
}

Opt3::Opt3(const Combination& edges) noexcept : Opt(edges) {
    /*
    According to the image from https://github.com/ozanyerli/tsp3opt
    Date of access: 04.03.2025, commit a8d61593a0db4ea9642298678bbc62f1cf6cb9da
    Letters A, B, C, D, E, F are calculated from top left vertex to top right vertex
    Combinations in the picture (according to their case numbers):
    (a) - 0, (b) - 3, (c) - 2, (d) - 1, (e) - 6, (f) - 5, (g) - 4, (h) - 7
    */
    // Maybe this could be written better using macro or loops
    auto A = edges[0].from;
    auto B = edges[0].to;
    auto C = edges[1].from;
    auto D = edges[1].to;
    auto E = edges[2].from;
    auto F = edges[2].to;
    // Combinations in the order from (b) to (h):
    combinations = {
        {
            {A, C},
            {B, D},
            {E, F}
        },
        {
            {A, B},
            {C, E},
            {D, F}
        },
        {
            {A, E},
            {D, C},
            {B, F}
        },
        {
            {A, D},
            {E, C},
            {B, F}
        },
        {
            {A, E},
            {D, B},
            {C, F}
        },
        {
            {A, C},
            {B, E},
            {D, F}
        },
        {
            {A, D},
            {E, B},
            {C, F}
        },
    };
}