#pragma once

#include <string>
#include <unordered_map>

#include "View.hpp"

using namespace std;

enum class Flags {
    Input,
    Output
};

static const unordered_map<Flags, string> flags_strings{
    {Flags::Input, "--input"},
    {Flags::Output, "--output"}
};

class CMDParamsParser {
private:
    unordered_map<string, string> params;
public:
    CMDParamsParser(int argc, char* argv[]);
    UPInputView get_input_view() const noexcept;
};