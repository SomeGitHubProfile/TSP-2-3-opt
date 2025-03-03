#include <iostream>

#include "ConsoleView.h"
#include "Model.h"

using namespace std;

void print_path(const Path& path) {
    cout << "Path length: " << path.length << '\n';
    cout << "Vertices order:\n";
    for (size_t i = 0; i < path.size; ++i) {
        cout << (path.vertices[i] + 1) << ' ';
    }
    cout << '\n';
}

int main() {
    ConsoleView view;
    view.set_mode();
    view.set_k();
    view.set_vertices();

    TSP_Solver solver(view.get_params());
    Result result = solver.solve();
    cout << "Time: " << result.time.count() << " ns\n";
    cout << "Initial path:\n";
    print_path(result.initial_path);
    cout << "Result path:\n";
    print_path(result.path);
    return 0;
}