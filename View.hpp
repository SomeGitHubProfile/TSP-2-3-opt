#pragma once

#include <memory>

#include "TSPSolverParams.hpp"
#include "Result.hpp"

using namespace std;

class OutputView {
public:
    virtual void output(const Result&) = 0;
};

typedef unique_ptr<OutputView> UPOutputView;

class InputView {
protected:
    TSPSolverParams params;

public:
    inline TSPSolverParams get_params() const noexcept {
        return params;
    }

    virtual void input() = 0;
    virtual UPOutputView get_output_view() const noexcept = 0;
};

typedef unique_ptr<InputView> UPInputView;