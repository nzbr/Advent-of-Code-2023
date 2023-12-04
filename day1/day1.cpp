// INTERFACE

#include <filesystem>
#include <ranges>
#include <algorithm>
#include "../shared/util.h"

using namespace std;
using namespace std::ranges;

void task1();

void task2();

// IMPLEMENTATION

auto lines = load_file((filesystem::path("..") / "day1" / "day1.txt").string());

int main() {

    task1();
    task2();

    return 0;
}

void task1() {
    unsigned long sum = 0;

    for (const auto &line: lines) {
        string digits;
        ranges::copy(
                line
                | views::filter([](const auto &s) { return s >= '0' && s <= '9'; }),
                back_inserter(digits)
        );
        auto numStr = string(1, digits.front()) + string(1, digits.back());
        auto num = stoi(numStr);
        sum += num;
    }

    cout << sum << endl;
};

void task2() {
    unsigned long sum = 0;

    const auto numbers = vector<string>{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    vector<string> rNumbers;
    ranges::transform(numbers, back_inserter(rNumbers), [](auto s) {
        std::reverse(s.begin(), s.end());
        return s;
    });

    for (const auto &line: lines) {
        auto rLine = line;
        std::reverse(rLine.begin(), rLine.end());

        auto firstPos = line.length()+1;
        auto lastPos = line.length()+1;
        char first;
        char last;

        for (int i = 0; i < 9; ++i) {
            auto s = to_string(i+1);
            auto cfPos = std::min(line.find(numbers[i]), line.find(s));
            auto clPos = std::min(rLine.find(rNumbers[i]), rLine.find(s));
            if (cfPos < firstPos) {
                firstPos = cfPos;
                first = s[0];
            }
            if (clPos < lastPos) {
                lastPos = clPos;
                last = s[0];
            }
        }

        auto numStr = string(1, first) + string(1, last);
        auto num = stoi(numStr);
        sum += num;
    }

    cout << sum << endl;
}