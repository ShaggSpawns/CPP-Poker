#pragma once
#include "Player.h"

class Board {
private:
	Card deck[52];
	Card communityCards[5];
	Player players[8];
	int deckSize = 0;
	int numPlayers = 0;
	int numCommunityCards = 0;
	std::string hands[10] = { "High Card", "Pair", "Two Pair", "Three", "Sraight", "Flush", "Full House", "Four", "Sraight Flush", "Royal Flush" };
public:
	Board();
	void shuffle();
	void addPlayer(Player p) { players[numPlayers++] = p; }
	Player & getPlayer(int index) { return players[index]; }
	Player getWinner();

	// Check current cards
	Card drawCard() {
		if (deckSize == 0) {
			deckSize = 52;
			shuffle();
		}

		return deck[--deckSize];
	}
	void dealAll() {
		for (int i = 0; i < numPlayers; i++) {
			players[i].addCard(drawCard());
			players[i].addCard(drawCard());
		}
	}
	void addCommunityCards() {
		for (int i = 0; i < 5; i++) {
			communityCards[numCommunityCards++] = drawCard();
		}
	}
	void showCards(int num) {
		for (int i = 0; i < num; i++) {
			std::cout << communityCards[i].getCard() << " ";
		}
		std::cout << std::endl << std::endl;
	}
	void printBoard() {
		for (int i = 0; i < 5; i++) {
			std::cout << communityCards[i].getCard() << " ";
		}
		std::cout << std::endl << std::endl;
		for (int i = 0; i < numPlayers; i++) {
			std::cout << players[i].getName() << " " << players[i].getCards() << " " << hands[players[i].getHand(communityCards, 5)] << std::endl;
		}
	}
	Card getCard(int index) { return deck[index]; }
	void clear() {
		deckSize = 0;
		numCommunityCards = 0;
		for (int i = 0; i < numPlayers; i++) {
			players[i].clear();
		}
	}
};


Board::Board() {
	for (int i = 0; i < 52; i++) {
		deck[i] = Card((Rank)(i % 13), (Suit)(i / 13));
	}
}

void Board::shuffle() {
	std::srand(unsigned(std::time(0)));
	std::random_shuffle(&deck[0], &deck[52]);
}

Player Board::getWinner() {
	Hand bestHand = players[0].getHand(communityCards, 5);
	Hand currentHand;
	int bestPlayer = 0;
	for (int i = 1; i < numPlayers; i++) {
		currentHand = players[i].getHand(communityCards, 5);
		if (currentHand > bestHand) {
			bestPlayer = i;
			bestHand = currentHand;
		}
	}
	return players[bestPlayer];
}
