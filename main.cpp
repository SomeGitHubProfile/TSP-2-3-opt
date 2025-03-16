#include <iostream>

#include "CMDParamsParser.hpp"
#include "View.hpp"
#include "Model.hpp"

int main(int argc, char* argv[]) {
    try {
        CMDParamsParser params_parser = CMDParamsParser(argc, argv);
        UPInputView input_view = params_parser.get_input_view();
        input_view->input();
        TSPSolver solver(input_view->get_params());
        Result result = solver.solve();
        UPOutputView output_view = input_view->get_output_view();
        output_view->output(result);
    } catch (const exception& e) {
        cout << "Error!\n";
        cout << e.what() << '\n';
        return 1;
    }
    return 0;
}