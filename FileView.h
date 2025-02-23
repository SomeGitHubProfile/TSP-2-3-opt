#pragma once

#include "View.h"

using namespace std;

class ConsoleView : public View {
public:
    ConsoleView(const char* path);
    virtual void set_mode() noexcept override;
    virtual void set_vertices() noexcept override;
    virtual void set_k() noexcept override;
};