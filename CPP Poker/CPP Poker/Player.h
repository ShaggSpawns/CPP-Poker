#pragma once
#include "Card.h"
#include <algorithm>
#include <ctime>

enum Hand {
	HIGH_CARD,
	PAIR,
	TWO_PAIR,
	THREE_OF_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_KIND,
	STRAIGHT_FLUSH,
	ROYAL_FLUSH
};

class Player {
private:
	Card hand[2];
	Rank rankHandHigh;
	int numCards = 0;
	Suit suitHandHigh;
	std::string name;
	void getNextSuit(int arr[4], int & currentSuit);
public:
	Hand getHand(Card communityCards[5], int numCards);
	Player() {}
	Player(std::string name) { this->name = name; }
	std::string getCards();
	void addCard(Card c) { hand[numCards++] = c; }
	void setCards(Card c1, Card c2) { hand[0] = c1; hand[1] = c2; }
	std::string getName() { return name; }
	void clear() {
		numCards = 0;
	}
};
