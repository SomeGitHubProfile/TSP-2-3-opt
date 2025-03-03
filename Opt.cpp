#include "Opt.h"

Opt::Opt() noexcept : initial_combination(0), combinations(0) {}

Opt::Opt(const Combination& edges) noexcept : initial_combination(edges), combinations(0) {}

Opt2::Opt2(const Combination& edges) noexcept : Opt(edges) {
    combinations = {
        {
            {edges[0].from, edges[1].from, true},
            {edges[0].from, edges[1].from, false}
        }
    };
}

Opt3::Opt3(const Combination& edges) noexcept : Opt(edges) {
    combinations = {{
            //TODO
    }};
}