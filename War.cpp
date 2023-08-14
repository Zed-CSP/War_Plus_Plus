#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

class Card {
public:
    Card(int rank, int suit) : rank(rank), suit(suit) {}

    int getRank() const { return rank; }
    int getSuit() const { return suit; }

    void display() const {
        std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        std::string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        std::cout << ranks[rank-2] << " of " << suits[suit] << std::endl;
    }

private:
    int rank; // 2 to 14 (2 to Ace)
    int suit; // 0 to 3 (Hearts, Diamonds, Clubs, Spades)
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


