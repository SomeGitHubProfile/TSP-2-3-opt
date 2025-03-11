#pragma once

#include <string>

#include "View.hpp"
#include "Result.hpp"

using namespace std;

class FileInputView : public InputView {
private:
    string path;
public:
    FileInputView(const string&) noexcept;
    virtual void input() override;
    virtual UPOutputView get_output_view(const Result& _result) const noexcept override;
};

class FileOutputView : public OutputView {
private:
    string path;
public:
    FileOutputView(const Result&, const string&) noexcept;
    virtual void output() override;
};