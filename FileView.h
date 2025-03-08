#pragma once

#include "View.h"

#include <string>

class FileInputView : public InputView {
private:
    std::string path;
public:
    FileInputView(const std::string&) noexcept;
    void read_file() noexcept;
};