#include "Path.hpp"

Path::Path() noexcept : length(0), vertices() {}

Path::Path(size_t size, long double _length) noexcept : length(_length), vertices(size) {}

void Path::optimize(const Combination& combination, long double distance_diff) noexcept {
    vector<size_t> new_vertices(vertices.size());
    size_t i = 0, j = 0;
    auto previous_edge = combination.begin();
    auto next_edge = previous_edge + 1;
    for (; i < previous_edge->from; ++i) {
        new_vertices[i] = vertices[i];
    }
    for (; next_edge != combination.end(); previous_edge = next_edge++) {
        new_vertices[i++] = vertices[previous_edge->from];
        int step = static_cast<int>(previous_edge->to < next_edge->from) * 2 - 1; // -1 if false, 1 if true
        for (j = previous_edge->to; j != next_edge->from; j += step) {
            new_vertices[i++] = vertices[j];
        }
    }
    new_vertices[i++] = vertices[previous_edge->from];
    for (j = previous_edge->to; j < vertices.size(); ++j) {
        new_vertices[i++] = vertices[j];
    }
    vertices = new_vertices;
    length -= distance_diff;
    return;
}