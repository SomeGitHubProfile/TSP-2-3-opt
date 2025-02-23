#pragma once

struct Path {
    size_t size;
    long double length;
    size_t* vertices;

    Path() noexcept;
    Path(size_t _size, long double _length = 0) noexcept;
    Path(const Path& rhs);
    Path& operator=(const Path& rhs);
    ~Path();
};