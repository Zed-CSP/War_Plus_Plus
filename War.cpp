#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

class Card {
private:
    int value;          // 1-13 (Ace through King)
    std::string suit;   // "Hearts", "Diamonds", "Clubs", "Spades"
    std::string name;   // e.g., "Ace of Hearts", "2 of Diamonds", ...

public:
    Card(int v, const std::string& s) : value(v), suit(s) {
        name = valueToString() + " of " + suit;
    }

    int getValue() const { return value; }

    std::string getName() const { return name; }

private:
    std::string valueToString() const {
        switch (value) {
            case 1: return "Ace";
            case 11: return "Jack";
            case 12: return "Queen";
            case 13: return "King";
            default: return std::to_string(value);
        }
    }
};

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() {
        for (int i = 1; i <= 13; i++) {
            for (int j = 0; j < 4; j++) {
                std::string suit = j == 0 ? "Hearts" : j == 1 ? "Diamonds" : j == 2 ? "Clubs" : "Spades";
                std::string name = std::to_string(i) + " of " + suit;
                cards.push_back(Card(i, name));
            }
        }
        shuffle();
    }

    void shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}


    Card draw() {
        Card c = cards.back();
        cards.pop_back();
        return c;
    }

    bool isEmpty() const {
        return cards.empty();
    }
};


