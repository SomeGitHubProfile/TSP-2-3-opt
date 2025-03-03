#pragma once

struct Point {
    size_t index;
    size_t value;
    Point() :
        index(0),
        value(0) {}
    Point(size_t _index, size_t _value) :
        index(_index),
        value(_value) {}
};

struct Edge {
    Point from;
    Point to;
    Edge() :
        from(),
        to() {}
    Edge(Point _from, Point _to) :
        from(_from),
        to(_to) {}
};