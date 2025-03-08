#include "ConsoleView.h"

#include <iostream>

using namespace std;

void ConsoleInputView::set_mode() noexcept {
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

void ConsoleInputView::set_vertices() noexcept {
    params.delete_vertices();

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

void ConsoleInputView::set_k() noexcept {
    cout << "Set k: ";
    cin >> params.k;
    return;
}

void ConsoleInputView::input() noexcept {
    set_mode();
    set_k();
    set_vertices();
    return;
}

ConsoleOutputViewResult::ConsoleOutputViewResult(const Result& result) noexcept : OutputViewResult(result) {}

void ConsoleOutputViewResult::print_path(const Path& path) const noexcept {
    cout << "Path length: " << path.length << '\n';
    cout << "Vertices order:\n";
    for (size_t i = 0; i < path.size; ++i) {
        cout << (path.vertices[i] + 1) << ' ';
    }
    cout << '\n';
}

void ConsoleOutputViewResult::output() noexcept {
    cout << "Initial path:\n";
    print_path(result.initial_path);
    cout << '\n';
    for (const Solution& solution : result.solutions) {
        cout << "Solution by algorithm " << solution.algorithm_name << ":\n";
        cout << "Time: " << solution.time.count() << " ns\n";
        cout << "Path:\n";
        print_path(solution.path);
        cout << '\n';
    }
    return;
}