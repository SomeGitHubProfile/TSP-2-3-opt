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
    // TODO 7 cases (init excluded)
    combinations = {
        {
            {},
            {},
            {}
        },
        {
            {},
            {},
            {}
        },
        {
            {},
            {},
            {}
        },
        {
            {},
            {},
            {}
        },
        {
            {},
            {},
            {}
        },
        {
            {},
            {},
            {}
        },
        {
            {},
            {},
            {}
        },
    };
}