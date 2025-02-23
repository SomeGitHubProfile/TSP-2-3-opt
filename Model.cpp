#include "Model.h"

#include <vector>
#include <algorithm>
#include <cmath>

#include "Random.h"

#define sqr(x) ((x) * (x))

#define path_vertex(i) params.vertices[path.vertices[i]]

long double calculate_distance(const Coords& a, const Coords& b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
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
        path.length += calculate_distance(path_vertex(i - 1), path_vertex(i));
    }
    return path;
}

Path TSP_Solver::opt2() const noexcept {
    Path path = generate_random_path();
    bool flag;
    do {
        flag = false;
        for (size_t i = 0; i < params.number_of_vertices; ++i) {
            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
                long double distance = calculate_distance(path_vertex(i), path_vertex(i + 1)) + calculate_distance(path_vertex(j), path_vertex(j + 1));
                long double new_distance = calculate_distance(path_vertex(i), path_vertex(j)) + calculate_distance(path_vertex(i + 1), path_vertex(j + 1));
                if (new_distance < distance) {
                    flag = true;
                    path.length += new_distance - distance;
                    std::reverse(path.vertices + i + 1, path.vertices + j + 1);
                }
            }
        }
    } while (flag);
    return path;
}

Path TSP_Solver::opt3() const noexcept {
    Path path = generate_random_path();
    bool flag;
    do {
        flag = false;
        for (size_t i = 0; i < params.number_of_vertices; ++i) {
            for (size_t j = i + 1; j < params.number_of_vertices; ++j) {
                
            }
        }
    } while (flag);
    return path;
}

TSP_Solver::TSP_Solver(const Params& _params) noexcept : params(_params) {}

Path TSP_Solver::solve() const noexcept {
    if (params.mode != Modes::Cycle) {
        // TODO only cycles are supported
        return Path();
    }
    if (params.k == 2) {
        return opt2();
    }
    return opt3();
}