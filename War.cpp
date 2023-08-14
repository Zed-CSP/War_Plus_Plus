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

class Game {
public:
    Game() : deck(), player1(), player2() {
        // Deal cards
        while(!deck.isEmpty()) {
            player1.addCard(deck.deal());
            player2.addCard(deck.deal());
        }
    }

    void play() {
        while(player1.hasCards() && player2.hasCards()) {
            Card card1 = player1.playCard();
            Card card2 = player2.playCard();

            std::cout << "Player 1 plays: "; card1.display();
            std::cout << "Player 2 plays: "; card2.display();

            if(card1.getRank() > card2.getRank()) {
                std::cout << "Player 1 wins this round!" << std::endl;
                player1.addCard(card1);
                player1.addCard(card2);
            }
            else if(card1.getRank() < card2.getRank()) {
                std::cout << "Player 2 wins this round!" << std::endl;
                player2.addCard(card1);
                player2.addCard(card2);
            }
            else {
                std::cout << "It's a tie!" << std::endl;
                // handle the "war" scenario here
            }
        }
        
        if(player1.hasCards()) {
            std::cout << "Player 1 wins the game!" << std::endl;
        } else {
            std::cout << "Player 2 wins the game!" << std::endl;
        }
    }

private:
    Deck deck;
    Player player1;
    Player player2;
};

int main() {
    Game game;
    game.play();
    return 0;
}