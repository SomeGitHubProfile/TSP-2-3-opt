#include "FileView.h"

#include <fstream>

using namespace std;

FileInputView::FileInputView(const string& _path) noexcept : path(_path) {}

void FileInputView::read_file() noexcept {
    ifstream file(path);
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
}