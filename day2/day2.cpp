// INTERFACE

#include <filesystem>
#include <iostream>
#include <regex>
#include <ranges>
#include <algorithm>
#include "../shared/util.h"

using namespace std;
using namespace std::ranges;

void task1();

void task2();

auto parseGames();

struct Round {
    int red;
    int green;
    int blue;
};

struct Game {
    int id;
    vector<Round> rounds;
};

// IMPLEMENTATION

auto lines = load_file((filesystem::path("..") / "day2" / "day2.txt").string());

int main() {
    task1();
    task2();

    return 0;
}

auto parseGames() {
    return lines | views::transform([](auto s) {
        const auto r = regex("^Game (\\d+):((?:(?: \\d+ [a-z]+,?)+;?)+)$");

        smatch m;
        regex_search(s, m, r);

        Game game;
        game.id = stoi(m[1]);
        ranges::transform(
                m[2].str() | views::split(';'),
                back_inserter(game.rounds),
                [](const auto &s) {
                    Round round{};
                    for (const auto &c: s | views::split(',')) {
                        const auto r = regex("^ ?(\\d+) ([a-z]+)$");

                        string cs;
                        ranges::copy(c, back_inserter(cs));
                        smatch m;
                        std::regex_search(cs, m, r);

                        if (m[2] == "red") {
                            round.red += stoi(m[1]);
                        } else if (m[2] == "green") {
                            round.green += stoi(m[1]);
                        } else if (m[2] == "blue") {
                            round.blue += stoi(m[1]);
                        }
                    }
                    return round;
                }
        );

        return game;
    });
}

void task1() {
    const auto maxRed = 12;
    const auto maxGreen = 13;
    const auto maxBlue = 14;

    auto idSum = 0;

    for (const auto &game: parseGames()) {
        auto valid = ranges::all_of(game.rounds, [&](const auto &round) {
            return round.red <= maxRed && round.green <= maxGreen && round.blue <= maxBlue;
        });
        if (valid) {
            idSum += game.id;
        }
    }

    cout << idSum << endl;
}

void task2() {
    auto powerSum = 0;

    for (const auto &game: parseGames()) {
        auto maxRed = 0;
        auto maxGreen = 0;
        auto maxBlue = 0;

        for (const auto &round: game.rounds) {
            maxRed = std::max(maxRed, round.red);
            maxGreen = std::max(maxGreen, round.green);
            maxBlue = std::max(maxBlue, round.blue);
        }

        powerSum += maxRed * maxGreen * maxBlue;
    }

    cout << powerSum << endl;
}
