#pragma once

#include "Params.h"

using namespace std;

class View {
protected:
    Params params;

public:
    inline Params get_params() const noexcept {
        return params;
    }

    virtual void set_mode() noexcept = 0;
    virtual void set_vertices() noexcept = 0;
    virtual void set_k() noexcept = 0;
};