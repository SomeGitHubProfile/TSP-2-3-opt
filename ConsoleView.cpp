#include "ConsoleView.h"

#include <iostream>

using namespace std;

void ConsoleView::set_mode() noexcept {
    cout << "Available modes:\n";
    for (size_t i = 0; i < number_of_modes; ++i) {
        cout << i << " = " << modes_strings[i] << '\n';
    }

    size_t input;
    cout << "Select mode: ";
    do {
        cin >> input;
    } while (number_of_modes <= input && cout << "Please, input correct mode: ");
    params.mode = static_cast<Modes>(input);
    return;
}

void ConsoleView::set_vertices() noexcept {
    if (params.vertices) {
        delete[] params.vertices;
    }

    cout << "Input number of vertices: ";
    cin >> params.number_of_vertices;

    if (!params.number_of_vertices) {
        params.vertices = nullptr;
        return;
    }

    params.vertices = new Coords[params.number_of_vertices];
    for (size_t i = 0; i < params.number_of_vertices; ++i) {
        cout << "Input " << (i + 1) << " vertex coordinates:\n";
        cin >> params.vertices[i].x >> params.vertices[i].y;
    }
    return;
}

void ConsoleView::set_k() noexcept {
    cout << "Set k: ";
    cin >> params.k;
    return;
}