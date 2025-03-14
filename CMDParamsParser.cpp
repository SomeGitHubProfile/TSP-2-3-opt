#include "CMDParamsParser.hpp"

#include <stdexcept>

#include "ConsoleView.hpp"
#include "FileView.hpp"

#define mget(map, key) ((map).find(key)->second)

#define get_param(key) mget(params, mget(flags_strings, key))

CMDParamsParser::CMDParamsParser(int argc, char* argv[]) {
    for (auto flag_string : flags_strings) {
        params[flag_string.second] = "";
    }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i++];
        if (params.find(arg) == params.end()) {
            throw invalid_argument("Error: invalid argument '" + arg + "'.\n");
        }
        if (argc <= i) {
            throw invalid_argument("Error: '" + arg + "' flag requires a file name.\n");
        }
        params[arg] = argv[i];
    }
}

UPInputView CMDParamsParser::get_input_view() const noexcept {
    if (get_param(Flags::Input).empty()) {
        return make_unique<ConsoleInputView>();
    }
    return make_unique<FileInputView>(get_param(Flags::Output));
}