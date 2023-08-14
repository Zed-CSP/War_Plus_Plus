#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

class Controller {
public:
    Controller() : game() {}

    void run() {
        displayWelcomeMessage();
        while (game.isOngoing()) {
            displayGameState();
            game.playRound();
            displayRoundWinner();
            pauseGame();
        }
        displayGameWinner();
    }

private:
    void pauseGame() const {
        std::cout << "Press enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void displayWelcomeMessage() const {
        std::cout << "Welcome to the game of War!" << std::endl;
        std::cout << "Two players will draw a card, and the player with the higher card wins the round." << std::endl;
        std::cout << "In the event of a tie, a war is declared!" << std::endl;
        std::cout << "Press enter to start the game...";
        pauseGame();
    }

    void displayGameState(){
        std::cout << "Player 1 has " << player1.getHandSize() << " cards." << std::endl;
        std::cout << "Player 2 has " << player2.getHandSize() << " cards." << std::endl;
    }

    void displayRoundWinner() const {
        // Here, you can use game's method to get the winner of the round and display it.
        int roundWinner = game.getRoundWinner();
        if(roundWinner == 1) {
            std::cout << "Player 1 wins this round!" << std::endl;
        } else if(roundWinner == 2) {
            std::cout << "Player 2 wins this round!" << std::endl;
        } else {
            std::cout << "It's a WAR!" << std::endl;
        }
    }

    void displayRoundWinner(int player) {
        std::cout << "Player " << player << " wins this round!" << std::endl;
        pauseGame();
    }

    void clearScreen() {
        std::cout << std::string(100, '\n');
    }

    Game game;
};

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
        hand.push_back(card); //adding card to the end of hand inorder to prevent broken playstyle
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
        Controller.displayWelcomeMessage();

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
                handleWar(card1, card2);
            }
        }
        
        if(player1.hasCards()) {
            std::cout << "Player 1 wins the game!" << std::endl;
        } else {
            std::cout << "Player 2 wins the game!" << std::endl;
        }
    }

private:
    void handleWar(Card& card1, Card& card2) {
        std::vector<Card> warPile;
        warPile.push_back(card1);
        warPile.push_back(card2);

        while (true) {
            if (!player1.hasCards() || !player2.hasCards()) {
                if (player1.hasCards()) {
                    for (const Card& card : warPile) {
                        player1.addCard(card);
                    }
                } else {
                    for (const Card& card : warPile) {
                        player2.addCard(card);
                    }
                }
                return;
            }

            for (int i = 0; i < 3 && player1.hasCards() && player2.hasCards(); i++) {
                warPile.push_back(player1.playCard());
                warPile.push_back(player2.playCard());
            }

            Card warCard1 = player1.playCard();
            Card warCard2 = player2.playCard();
            std::cout << "Player 1's war card: "; warCard1.display();
            std::cout << "Player 2's war card: "; warCard2.display();

            if (warCard1.getRank() > warCard2.getRank()) {
                std::cout << "Player 1 wins the war!" << std::endl;
                warPile.push_back(warCard1);
                warPile.push_back(warCard2);
                for (const Card& card : warPile) {
                    player1.addCard(card);
                }
                return;
            } else if (warCard1.getRank() < warCard2.getRank()) {
                std::cout << "Player 2 wins the war!" << std::endl;
                warPile.push_back(warCard1);
                warPile.push_back(warCard2);
                for (const Card& card : warPile) {
                    player2.addCard(card);
                }
                return;
            } else {
                std::cout << "Another tie! The war continues!" << std::endl;
                warPile.push_back(warCard1);
                warPile.push_back(warCard2);
            }
        }
    }

    Deck deck;
    Player player1;
    Player player2;
};

int main() {
    Game game;
    game.play();
    return 0;
}