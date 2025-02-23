#include "Params.h"

Params::Params() noexcept : mode(Modes::Cycle), number_of_vertices(0), k(0), vertices(nullptr) {}

Params::Params(const Params& rhs) : mode(rhs.mode), number_of_vertices(rhs.number_of_vertices), k(rhs.k) {
    vertices = new Coords[number_of_vertices];
    for (size_t i = 0; i < number_of_vertices; ++i) {
        vertices[i] = rhs.vertices[i];
    }
}

Params::~Params() {
    delete[] vertices;
}