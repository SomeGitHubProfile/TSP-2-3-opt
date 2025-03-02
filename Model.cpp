#include "Model.h"

#include <vector>
#include <algorithm>
#include <cmath>

#include "Random.h"

#define sqr(x) ((x) * (x))

#define path_vertex(i) params.vertices[path.vertices[i]]

#define get_point(i) Point(i, path.vertices[i])

long double calculate_distance(const Coords& a, const Coords& b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

long double TSP_Solver::calculate_distance(const Path& path, const Combination& combination) const noexcept {
    long double distance = 0;
    for (auto edge : combination.edges) {
        distance += ::calculate_distance(path_vertex(edge.from.index), path_vertex(edge.to.index));
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
    Combination minimal_combination = opt->combinations[0];
    long double minimal_distance = calculate_distance(path, minimal_combination);
    bool flag = false;
    for (Combination combination : opt->combinations) {
        long double distance = calculate_distance(path, combination);
        if (distance < minimal_distance) {
            flag = true;
            minimal_distance = distance;
            minimal_combination = combination;
        }
    }
    return {minimal_combination, minimal_distance, flag};
}

Path TSP_Solver::opt2() const noexcept {
    Path path = generate_random_path();
    bool flag;
    do {
        flag = false;
        for (size_t i = 0; i < params.number_of_vertices; ++i) {
            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
                Opt* opt = new Opt2(vector<Edge>({
                    {get_point(i), get_point(i + 1)},
                    {get_point(j), get_point(j + 1)}
                }));
                auto [combination, distance, new_flag] = get_miminal_combination(path, opt);
                if (!new_flag) {
                    continue;
                }
                flag = true;
                path.length -= distance;
                for (auto edge : combination.segments_to_reverse) {
                    std::reverse(path.vertices + edge.from.index, path.vertices + edge.to.index);
                }
                for (auto edge : combination.edges) {

                }
            }
        }
    } while (flag);
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

Path TSP_Solver::opt3() const noexcept {
    Path path = generate_random_path();
    bool flag;
    do {
        flag = false;
        for (size_t i = 0; i < params.number_of_vertices; ++i) {
            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
                Opt2(vector<Edge>({
                    {nullptr, nullptr},
                    {nullptr, nullptr},
                    {nullptr, nullptr}
                }));
            }
        }
    } while (flag);
}

TSP_Solver::TSP_Solver(const Params& _params) noexcept : params(_params) {}

Result TSP_Solver::solve() const noexcept {
    auto start = std::chrono::high_resolution_clock::now();
    Path path = params.k == 2 ? opt2() : opt3();
    auto finish = std::chrono::high_resolution_clock::now();
    auto time = finish - start;
    return {path, time};
}