#include "Model.h"

#include <vector>
#include <algorithm>
#include <cmath>

#include "Random.h"

#define sqr(x) ((x) * (x))
#define path_vertex(i) params.vertices[path.vertices[i]]
#define get_edge(i) {i, i + 1}

long double calculate_distance(const Coords& a, const Coords& b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

long double TSP_Solver::calculate_distance(const Path& path, const Combination& combination) const noexcept {
    long double distance = 0;
    for (const Edge& edge : combination) {
        distance += ::calculate_distance(path_vertex(edge.from), path_vertex(edge.to));
    }
    return distance;
}

Path TSP_Solver::generate_random_path() const noexcept {
    Path path(params.number_of_vertices + static_cast<size_t>(params.mode == Modes::Cycle), 0);
    for (size_t i = 0; i < params.number_of_vertices; ++i) {
        path.vertices[i] = i;
    }
    shuffle(path.vertices, path.vertices + params.number_of_vertices, random::g);
    if (params.mode == Modes::Cycle) {
        path.vertices[path.size - 1] = path.vertices[0];
    }

    for (size_t i = 1; i < path.size; ++i) {
        path.length += ::calculate_distance(path_vertex(i - 1), path_vertex(i));
    }
    return path;
}

tuple<Combination, long double, bool> TSP_Solver::get_miminal_combination(const Path& path, Opt* opt) const noexcept {
    Combination minimal_combination = opt->initial_combination;
    long double initial_distance = calculate_distance(path, minimal_combination);
    long double minimal_distance = initial_distance;
    bool can_improve = false;
    for (Combination combination : opt->combinations) {
        long double distance = calculate_distance(path, combination);
        if (distance < minimal_distance) {
            can_improve = true;
            minimal_distance = distance;
            minimal_combination = combination;
        }
    }
    return {minimal_combination, initial_distance - minimal_distance, can_improve};
}

Path TSP_Solver::opt2(Path path) const noexcept {
    bool flag;
    do {
        flag = false;
        for (size_t i = 0; i < params.number_of_vertices; ++i) {
            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
                Opt* opt = new Opt2({get_edge(i), get_edge(j)});
                auto [combination, distance_diff, can_improve] = get_miminal_combination(path, opt);
                delete opt;
                if (can_improve) {
                    flag = true;
                    path.optimize(combination, distance_diff);
                }
            }
        }
    } while (flag);
    return path;
}

Path TSP_Solver::opt3(Path path) const noexcept {
    bool flag;
    do {
        flag = false;
        for (size_t i = 0; i < params.number_of_vertices; ++i) {
            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
                for (size_t k = j + 1; k < params.number_of_vertices; ++k) {
                    Opt* opt = new Opt3({get_edge(i), get_edge(j), get_edge(k)});
                    auto [combination, distance_diff, can_improve] = get_miminal_combination(path, opt);
                    delete opt;
                    if (can_improve) {
                        flag = true;
                        path.optimize(combination, distance_diff);
                    }
                }
            }
        }
    } while (flag);
    return path;
}

TSP_Solver::TSP_Solver(const Params& _params) noexcept : params(_params) {}

Solution TSP_Solver::solve(Path random_path, Path(TSP_Solver::* opt)(Path) const noexcept, const char* algorithm_name) const noexcept {
    auto start = std::chrono::high_resolution_clock::now();
    Path path = (this->*opt)(random_path);
    auto finish = std::chrono::high_resolution_clock::now();
    auto time = finish - start;
    return {path, time, algorithm_name};
}

Result TSP_Solver::solve() const noexcept {
    Path random_path = generate_random_path();
    switch (params.k) {
        case 1:
            return {
                random_path,
                {
                    solve(random_path, &TSP_Solver::opt2, "opt-2"),
                    solve(random_path, &TSP_Solver::opt3, "opt-3")
                }
            };
        case 2:
            return {
                random_path,
                {solve(random_path, &TSP_Solver::opt2, "opt-2")}
            };
        case 3:
            return {
                random_path,
                {solve(random_path, &TSP_Solver::opt3, "opt-3")}
            };
        default:
            break;
    }
    return Result();
}