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
    Result result = solver.solve();
    cout << "Time: " << result.time.count() << " ns\n";
    cout << "Path length: " << result.path.length << '\n';
    cout << "Vertices order:\n";
    for (size_t i = 0; i < result.path.size; ++i) {
        cout << (result.path.vertices[i] + 1) << ' ';
    }
    cout << '\n';
    return 0;
}