#pragma once

#include <string>

#include "View.hpp"
#include "Result.hpp"

using namespace std;

class FileInputView : public InputView {
private:
    string input_path;
    string output_path;
public:
    FileInputView(const string&) noexcept;
    FileInputView(const string&, const string&) noexcept;
    virtual void input() override;
    virtual UPOutputView get_output_view() const noexcept override;
};

class FileOutputView : public OutputView {
private:
    string path;

    void make_directories() const noexcept;
public:
    FileOutputView(const string&) noexcept;
    virtual void output(const Result&) override;
};