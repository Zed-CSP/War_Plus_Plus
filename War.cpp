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
public:
    Deck() {
        for(int suit = 0; suit < 4; ++suit) {
            for(int rank = 2; rank <= 14; ++rank) {
                cards.push_back(Card(rank, suit));
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());  // mt19937 is a random number generator
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card deal() {
        Card top = cards.back();
        cards.pop_back();
        return top;
    }

    bool isEmpty() const {
        return cards.empty();
    }

private:
    std::vector<Card> cards;
};

class Player {
public:
    void addCard(const Card& card) {
        hand.push_back(card);
    }

    Card playCard() {
        Card top = hand.front();
        hand.erase(hand.begin());
        return top;
    }

    bool hasCards() const {
        return !hand.empty();
    }

private:
    std::vector<Card> hand;
};
