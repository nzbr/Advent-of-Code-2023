// INTERFACE

#include <filesystem>
#include <ranges>
#include <algorithm>
#include "../shared/util.h"

using namespace std;

void task1();

void task2();

// IMPLEMENTATION

auto lines = load_file((filesystem::path("..") / "day3" / "day3.txt").string());

int main() {
    task1();
    cout << endl;
    task2();

    return 0;
}

vector<string> padLines() {
    vector<string> paddedLines;
    ranges::transform(lines, back_inserter(paddedLines), [](auto s) {
        return "." + s + ".";
    });

    string padding(paddedLines.front().length(), '.');
    paddedLines.insert(paddedLines.begin(), padding);
    paddedLines.emplace_back(padding);
    return paddedLines;
}

void task1() {
    auto paddedLines = ::padLines();

    auto start = 0;
    auto num = 0;
    auto sum = 0;

    for (auto x = 1; x < paddedLines.size() - 1; x++) {
        // go until the end of the line, so that numbers that touch the border are counted
        for (auto y = 1; y < paddedLines.front().length(); y++) {
            auto c = paddedLines[x][y];
            if (c >= '0' && c <= '9') {
                if (start == 0) {
                    start = y;
                }
                num = num * 10 + c - '0';
            } else {
                if (start != 0) {
                    vector<tuple<int, int>> candidates;
                    for (auto i = x - 1; i <= x + 1; i++) {
                        for (auto j = start - 1; j <= y; j++) {
                            candidates.emplace_back(i, j);
                        }
                    }

                    auto valid = ranges::any_of(candidates, [&paddedLines](auto t) {
                        auto [i, j] = t;
                        auto c = paddedLines[i][j];
                        return (c < '0' || c > '9') && c != '.';
                    });

                    if (valid) {
                        sum += num;
                    }

                    start = 0;
                    num = 0;
                }
            }
        }
    }

    cout << sum << endl;
}

void task2() {
    auto paddedLines = ::padLines();

    auto sum = 0;

    for (auto x = 1; x < paddedLines.size() - 1; x++) {
        for (auto y = 1; y < paddedLines.front().length() - 1; y++) {
            if (paddedLines[x][y] == '*') {
                int aX;
                int aY;
                auto a = 0;
                auto b = 0;
                for (auto i = x - 1; i <= x + 1; i++) {
                    for (auto j = y - 1; j <= y + 1; j++) {
                        auto c = paddedLines[i][j];
                        if (c >= '0' && c <= '9') {
                            if (a == 0) {
                                aX = i;
                                aY = j;
                                while (paddedLines[aX][aY] >= '0' && paddedLines[aX][aY] <= '9') {
                                    aY--;
                                }
                                aY++;
                                auto tY = aY;
                                while (paddedLines[aX][tY] >= '0' && paddedLines[aX][tY] <= '9') {
                                    a = a * 10 + paddedLines[aX][tY] - '0';
                                    tY++;
                                }
                            } else if (b == 0) {
                                auto bY = j;
                                while (paddedLines[i][bY] >= '0' && paddedLines[i][bY] <= '9') {
                                    bY--;
                                }
                                bY++;
                                if (i == aX && bY == aY) {
                                    continue; // same number
                                }
                                while (paddedLines[i][bY] >= '0' && paddedLines[i][bY] <= '9') {
                                    b = b * 10 + paddedLines[i][bY] - '0';
                                    bY++;
                                }
                            }
                        }
                    }
                }

                sum += a * b;
            }
        }
    }

    cout << sum << endl;
}
