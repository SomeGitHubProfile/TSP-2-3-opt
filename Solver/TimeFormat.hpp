#pragma once

#include <string>
#include <unordered_map>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

float time_to_float(long long time, unsigned char precision) {
    float p = pow(10, precision);
    return round(time * p / 1000.0) / p;
}

pair<float, string> format_time(nanoseconds time, unsigned char precision = 2) {
    long long ns = duration_cast<nanoseconds>(time).count();
    if (ns < 1000) {
        return {ns, "nanoseconds"};
    }

    long long mcs = duration_cast<microseconds>(time).count();
    if (mcs < 1000) {
        return {time_to_float(ns, precision), "microseconds"};
    }

    long long mls = duration_cast<milliseconds>(time).count();
    if (mls < 1000) {
        return {time_to_float(mcs, precision), "milliseconds"};
    }

    long long s = duration_cast<seconds>(time).count();
    if (s < 1'000'000) {
        return {time_to_float(mls, precision), "seconds"};
    }

    return {s, "seconds"};
}