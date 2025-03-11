#pragma once

#include <memory>

#include "TSPSolverParams.hpp"
#include "Result.hpp"

using namespace std;

class OutputView {
protected:
    Result result;

public:
    OutputView(const Result& _result) noexcept : result(_result) {}

    virtual void output() = 0;
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
    virtual UPOutputView get_output_view(const Result&) const noexcept = 0;
};

typedef unique_ptr<InputView> UPInputView;