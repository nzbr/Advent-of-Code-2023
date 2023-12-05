// INTERFACE

#include <filesystem>
#include <ranges>
#include <algorithm>
#include <regex>
#include <set>
#include <queue>
#include "../shared/util.h"

using namespace std;

typedef unsigned int u32;

struct Card {
    int id{};
    set<u32> winning;
    vector<u32> yours;
};

auto parseCards();

void task1();

void task2();

// IMPLEMENTATION

auto lines = load_file((filesystem::path("..") / "day4" / "day4.txt").string());

int main() {
    task1();
    cout << endl;
    task2();

    return 0;
}

auto parseCards() {
    return lines | views::transform([](auto s) {
        const auto r = regex(R"(^Card +(\d+): ([\d ]+) \| ([\d ]+)$)");

        smatch m;
        regex_search(s, m, r);

        Card game;
        game.id = stoi(m[1].str());
        ranges::transform(
                m[2].str() | views::split(' ') | views::filter([](const auto &s) { return !s.empty(); }),
                inserter(game.winning, game.winning.end()),
                [](const auto &s) {
                    return parseNum(s);
                }
        );
        ranges::transform(
                m[3].str() | views::split(' '),
                back_inserter(game.yours),
                [](const auto &s) {
                    return parseNum(s);
                }
        );

        return game;
    });
}

void task1() {
    auto cards = parseCards();
    u32 score = 0;
    for (const auto &card: cards) {
        u32 winning = 0;
        for (const auto &y: card.yours) {
            if (card.winning.contains(y)) {
                winning++;
            }
        }
        if (winning > 0) {
            score += ((u32) 1) << (winning - 1);
        }
    }
    cout << score << endl;
}

long countCards(Card **cards, long **counts, u32 id) {
    long* count = (*counts) + id - 1;
    if (*count == -2) {
        throw runtime_error("infinite loop");
    } else if (*count != -1) {
        return *count;
    }

    *count = -2;
    auto card = (*cards) + id - 1;

    u32 winning = 0;
    for (const auto &y: card->yours) {
        if (card->winning.contains(y)) {
            winning++;
        }
    }

    *count = 1; // This one
    for (u32 i = 1; i <= winning; i++) {
        *count += countCards(cards, counts, id + i);
    }

    return *count;
}

void task2() {
    Card* cards = new Card[lines.size()];
    {
        u32 i = 0;
        for (const auto &card: parseCards()) {
            cards[i++] = card;
        }
    }

    u32 count = 0;
    long* cardCounts = new long[lines.size()];
    for (u32 i = 0; i < lines.size(); i++) {
        cardCounts[i] = -1;
    }

    queue<Card> q;
    for (u32 i = 0; i < lines.size(); i++) {
        q.push(cards[i]);
    }

    for (u32 i = 1; i <= lines.size(); i++) {
        count += countCards(
                &cards,
                &cardCounts,
                i
        );
    }

    delete[] cardCounts;

    cout << count << endl;
}
