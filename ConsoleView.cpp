#include "ConsoleView.hpp"

#include <iostream>

#include "FileView.hpp"
#include "TimeFormat.hpp"

void ConsoleInputView::set_mode() noexcept {
    cout << "Available modes:\n";
    for (auto mode : modes_strings) {
        cout << static_cast<size_t>(mode.second) << " = " << mode.first << '\n';
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
    cout << "Algorithm: k-opt. k = 1 means comparison mode.\nSet k: ";
    cin >> params.k;
    return;
}

void ConsoleInputView::set_output_file() noexcept {
    cout << "Enter path to the output file or press Enter to display the result in the console.\n";
    getline(cin, output_file);
    return;
}

void ConsoleInputView::input() noexcept {
    set_output_file();
    set_mode();
    set_k();
    set_vertices();
    return;
}

UPOutputView ConsoleInputView::get_output_view(const Result& result) const noexcept {
    if (output_file.empty()) {
        return make_unique<ConsoleOutputView>(result);
    }
    return make_unique<FileOutputView>(result, output_file);
}

ConsoleOutputView::ConsoleOutputView(const Result& result) noexcept : OutputView(result) {}

void ConsoleOutputView::print_path(const Path& path) const noexcept {
    cout << "Path length: " << path.length << '\n';
    cout << "Vertices order:\n";
    for (size_t vertex : path.vertices) {
        cout << (vertex + 1) << ' ';
    }
    cout << '\n';
}

void ConsoleOutputView::output() noexcept {
    cout << "Initial path:\n";
    print_path(result.initial_path);
    cout << '\n';
    for (const Solution& solution : result.solutions) {
        cout << "Solution by algorithm " << solution.algorithm_name << ":\n";
        pair<float, string> time = format_time(solution.time);
        cout << "Time: " << time.first << ' ' << time.second << '\n';
        print_path(solution.path);
        cout << '\n';
    }
    return;
}