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

//Path old_opt2() {
//    Path path = generate_random_path();
//    bool flag;
//    do {
//        flag = false;
//        for (size_t i = 0; i < params.number_of_vertices; ++i) {
//            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
//                long double distance = calculate_distance(path_vertex(i), path_vertex(i + 1)) + calculate_distance(path_vertex(j), path_vertex(j + 1));
//                long double new_distance = calculate_distance(path_vertex(i), path_vertex(j)) + calculate_distance(path_vertex(i + 1), path_vertex(j + 1));
//                if (new_distance < distance) {
//                    flag = true;
//                    path.length += new_distance - distance;
//                    std::reverse(path.vertices + i + 1, path.vertices + j + 1);
//                }
//            }
//        }
//    } while (flag);
//    return path;
//}

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
                auto [combination, distance, can_improve] = get_miminal_combination(path, opt);
                delete opt;
                if (!can_improve) {
                    continue;
                }
                flag = true;
                path.length -= distance;
                size_t* new_vertices = new size_t[path.size];
                size_t x = 0, y = 0;
                for (; x < i; ++x) {
                    new_vertices[x] = path.vertices[x];
                }
                auto previous_edge = combination.begin();
                auto next_edge = previous_edge + 1;
                for (; next_edge != combination.end(); previous_edge = next_edge++) {
                    new_vertices[x++] = path.vertices[previous_edge->from];
                    int step = static_cast<int>(previous_edge->to < next_edge->from) * 2 - 1; // -1 if false, 1 if true
                    for (y = previous_edge->to; y != next_edge->from; y += step) {
                        new_vertices[x++] = path.vertices[y];
                    }
                }
                new_vertices[x++] = path.vertices[previous_edge->from];
                for (y = previous_edge->to; y < path.size; ++y) {
                    new_vertices[x++] = path.vertices[y];
                }
                delete[] path.vertices;
                path.vertices = new_vertices;
            }
        }
    } while (flag);
    return path;
}

//Path TSP_Solver::opt3() const noexcept {
//    Path path = generate_random_path();
//    bool flag;
//    do {
//        flag = false;
//        for (size_t i = 0; i < params.number_of_vertices; ++i) {
//            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
//                for (size_t k = j + 1; k < params.number_of_vertices; ++k) {
//
//                }
//            }
//        }
//    } while (flag);
//    return path;
//}

Path TSP_Solver::opt3(Path path) const noexcept {
    /*bool flag;
    do {
        flag = false;
        for (size_t i = 0; i < params.number_of_vertices; ++i) {
            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
                Opt2(Combination({
                    {nullptr, nullptr},
                    {nullptr, nullptr},
                    {nullptr, nullptr}
                }));
            }
        }
    } while (flag);*/
    return path;
}

TSP_Solver::TSP_Solver(const Params& _params) noexcept : params(_params) {}

Result TSP_Solver::solve() const noexcept {
    Path random_path = generate_random_path();
    auto start = std::chrono::high_resolution_clock::now();
    Path path = params.k == 2 ? opt2(random_path) : opt3(random_path);
    auto finish = std::chrono::high_resolution_clock::now();
    auto time = finish - start;
    return {random_path, path, time};
}