#pragma once
#include <iostream>
#include <string>

enum Rank {
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};

enum Suit {
	Club,
	Diamond,
	Heart,
	Spade
};

class Card {
private:
	Rank rank;
	Suit suit;
	std::string rankLkup[13] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
	std::string suitLkup[4] = { "Club", "Diamond", "Heart", "Spade" };
public:
	Card() {};
	Card(Rank rank, Suit suit) {
		this->rank = rank;
		this->suit = suit;
	};
	Suit getSuit() { return suit; }
	std::string getSuitS() { return suitLkup[suit]; }
	Rank getRank() { return rank; }
	std::string getRankS() { return rankLkup[rank]; }
	std::string getCard() {
		return rankLkup[rank] + " (" + suitLkup[suit] + ")";
	}
};
