#include "Opt.hpp"

Opt::Opt() noexcept : initial_combination(0), combinations(0) {}

Opt::Opt(const Combination& edges) noexcept : initial_combination(edges), combinations(0) {}

Opt2::Opt2(const Combination& edges) noexcept : Opt(edges) {
    const size_t A = edges[0].from;
    const size_t B = edges[0].to;
    const size_t C = edges[1].from;
    const size_t D = edges[1].to;
    combinations = {
        {
            {A, C},
            {B, D}
        }
    };
}

Opt3::Opt3(const Combination& edges) noexcept : Opt(edges) {
    /*
    According to the image from https://github.com/ozanyerli/tsp3opt
    Date of access: 04.03.2025, commit a8d61593a0db4ea9642298678bbc62f1cf6cb9da
    Letters A, B, C, D, E, F are calculated from top left vertex to top right vertex (counterclockwise)
    Combinations in the picture (according to their case numbers):
    (a) - 0, (b) - 3, (c) - 2, (d) - 1, (e) - 6, (f) - 5, (g) - 4, (h) - 7
    */
    // Maybe this could be written better using macro and/or loops
    const size_t A = edges[0].from;
    const size_t B = edges[0].to;
    const size_t C = edges[1].from;
    const size_t D = edges[1].to;
    const size_t E = edges[2].from;
    const size_t F = edges[2].to;
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