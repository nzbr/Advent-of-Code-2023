#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

typedef uint32_t u32;

template<typename T>
u32 parseNum(T s) {
    u32 num = 0;
    for (const auto &c: s) {
        num = num * 10 + c - '0';
    }
    return num;
}

vector<string> load_file(const string& filename);
