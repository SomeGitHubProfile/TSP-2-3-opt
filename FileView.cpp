#include "FileView.hpp"

#include <fstream>
#include <sstream>

#include "json.hpp"

#include "ConsoleView.hpp"

using json = nlohmann::json;

FileInputView::FileInputView(const string& _input_path) noexcept :
    input_path(_input_path),
    output_path("") {}

FileInputView::FileInputView(const string& _input_path, const string& _output_path) noexcept :
    input_path(_input_path),
    output_path(_output_path) {}

void FileInputView::input() {
    ifstream file(input_path);
    string s;
    getline(file, s);
    sscanf_s(s.c_str(), "%zu", &params.number_of_vertices);
    params.delete_vertices();
    params.vertices = new Coords[params.number_of_vertices];
    for (size_t i = 0; i < params.number_of_vertices; ++i) {
        getline(file, s);
        istringstream stream(s);
        stream >> params.vertices[i].x >> params.vertices[i].y;
    }
    params.mode = Modes::Cycle;
    params.k = 1;
    return;
}


UPOutputView FileInputView::get_output_view() const noexcept {
    if (output_path.empty()) {
        return make_unique<ConsoleOutputView>();
    }
    return make_unique<FileOutputView>(output_path);
}

FileOutputView::FileOutputView(const string& _path) noexcept : path(_path) {}

void FileOutputView::output(const Result& result) {
    json j = result.to_json();
    ofstream file(path);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    } else {
        throw filesystem::filesystem_error(("Unable to open output file: " + path + '\n'), make_error_code(errc::no_such_file_or_directory));
    }
    return;
}