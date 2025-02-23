#pragma once

#include "View.h"

class ConsoleView : public View {
public:
    virtual void set_mode() noexcept override;
    virtual void set_vertices() noexcept override;
    virtual void set_k() noexcept override;
};