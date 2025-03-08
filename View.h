#pragma once

#include "Params.h"
#include "Result.h"

using namespace std;

class InputView {
protected:
    Params params;

public:
    inline Params get_params() const noexcept {
        return params;
    }

    virtual void input() = 0;
};

class OutputViewResult {
protected:
    Result result;

public:
    OutputViewResult(const Result& _result) noexcept : result(_result) {}

    virtual void output() = 0;
};