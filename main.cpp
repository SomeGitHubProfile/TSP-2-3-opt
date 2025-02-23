#include <iostream>

#include "ConsoleView.h"
#include "Model.h"

using namespace std;

int main() {
    ConsoleView view;
    view.set_mode();
    view.set_k();
    view.set_vertices();

    TSP_Solver solver(view.get_params());
    Path path = solver.solve();
    cout << "Path length: " << path.length << '\n';
    cout << "Vertices order:\n";
    for (size_t i = 0; i < path.size; ++i) {
        cout << (path.vertices[i] + 1) << ' ';
    }
    cout << '\n';
    return 0;
}