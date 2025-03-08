#pragma once

#include "View.h"

class ConsoleInputView : public InputView {
private:
    void set_mode() noexcept;
    void set_vertices() noexcept;
    void set_k() noexcept;

public:
    virtual void input() noexcept override;
};

class ConsoleOutputViewResult : public OutputViewResult {
private:
    void print_path(const Path& path) const noexcept;
public:
    ConsoleOutputViewResult(const Result&) noexcept;
    virtual void output() noexcept override;
};