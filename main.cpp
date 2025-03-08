#include "ConsoleView.h"
#include "Model.h"

#include <iostream>

int main() {
    try {
        unique_ptr<InputView> input_view = make_unique< ConsoleInputView>();
        input_view->input();
        TSP_Solver solver(input_view->get_params());
        Result result = solver.solve();
        unique_ptr<OutputViewResult> output_view = make_unique< ConsoleOutputViewResult>(result);
        output_view->output();
    } catch (const exception& e) {
        cout << "Error!\n";
        cout << e.what() << '\n';
    }
    return 0;
}