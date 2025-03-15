#pragma once

#include <string>

#include "View.hpp"
#include "Path.hpp"
#include "Result.hpp"

using namespace std;

class ConsoleInputView : public InputView {
private:
    string output_file;

    void set_mode() noexcept;
    void set_vertices() noexcept;
    void set_k() noexcept;
    void set_output_file() noexcept;

public:
    ConsoleInputView() noexcept {}
    virtual void input() noexcept override;
    virtual UPOutputView get_output_view(const Result&) const noexcept override;
};

class ConsoleOutputView : public OutputView {
private:
    void print_path(const Path& path) const noexcept;
public:
    ConsoleOutputView(const Result&) noexcept;
    virtual void output() noexcept override;
};