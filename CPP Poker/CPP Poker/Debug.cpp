#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <Windows.h>

enum Rank
{
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

enum Suit
{
	Club,
	Diamond,
	Heart,
	Spade
};

enum Hand
{
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

using namespace std;

class Card
{
private:
	Rank rank;
	Suit suit;
	string rankLkup[13] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
	string suitLkup[4] = { "Club", "Diamond", "Heart", "Spade" };
public:
	Card() {};
	Card(Rank rank, Suit suit) {
		this->rank = rank;
		this->suit = suit;
	};
	Suit getSuit() { return suit; }
	string getSuitS() { return suitLkup[suit]; }
	Rank getRank() { return rank; }
	string getRankS() { return rankLkup[rank]; }
	string getCard() {
		return rankLkup[rank] + " (" + suitLkup[suit] + ")";
	}
};

class Deck
{
private:
	Card deck[52];
	int deckSize = 0;
public:
	Deck();
	void shuffle();
	Card drawCard();
};

Deck::Deck()
{
	for (int i = 0; i < 52; i++)
		deck[i] = Card((Rank)(i % 13), (Suit)(i / 13));
}

void Deck::shuffle()
{
	srand(unsigned(time(0)));
	random_shuffle(&deck[0], &deck[52]);
}

Card Deck::drawCard()
{
	if (deckSize == 0)
	{
		deckSize = 52;
		shuffle();
	}

	return deck[--deckSize];
}


Hand evaluateHand(Card cards[], int numCards)
{
	int orderedCards[13][4] = {};
	int orderedCardsCombined[13] = {};

	for (int i = 0; i < numCards; i++)
	{
		orderedCards[cards[i].getRank()][cards[i].getSuit()]++;
		orderedCardsCombined[cards[i].getRank()]++;
	}

	int startStreak;
	int longestStreak = 0;
	{
		bool onStreak = false;
		int tempStartStreak;
		int streakCounter = 0;
		for (int i = 12; i >= 0; i--)
		{
			onStreak = orderedCardsCombined[i] != 0;
			if (onStreak)
			{
				tempStartStreak = i;
				streakCounter++;
			}
			else if (tempStartStreak == i + 1)
			{
				if (streakCounter > longestStreak)
				{
					startStreak = tempStartStreak;
					longestStreak = streakCounter;
				}
				streakCounter = 0;
			}
		}
		// Check low ace
		if (onStreak)
		{
			if (orderedCardsCombined[12] != 0)
				streakCounter++;
			if (streakCounter > longestStreak)
			{
				startStreak = tempStartStreak;
				longestStreak = streakCounter;
			}
		}
	}
	bool straight = longestStreak >= 5;

	bool straightFlush = false;
	bool royalFlush = false;

	if (straight)
	{
		int startFlushStreak;
		int longestFlushStreak = 0;

		for (int j = 0; j < 4; j++)
		{
			bool onStreak = false;
			int tempStartStreak;
			int streakCounter = 0;
			for (int i = startStreak + longestStreak - 1; i >= startStreak; i--)
			{
				onStreak = orderedCards[i][j] != 0;
				if (onStreak)
				{
					tempStartStreak = i;
					streakCounter++;
				}
				else if (tempStartStreak == i + 1)
				{
					if (streakCounter > longestFlushStreak)
					{
						startFlushStreak = tempStartStreak;
						longestFlushStreak = streakCounter;
					}
					streakCounter = 0;
				}
			}
			// Check low ace
			if (onStreak)
			{
				if (orderedCards[12][j] != 0)
					streakCounter++;
				if (streakCounter > longestFlushStreak)
				{
					startFlushStreak = tempStartStreak;
					longestFlushStreak = streakCounter;
				}
			}

			if (longestFlushStreak >= 5)
			{
				straightFlush = true;
				break;
			}
		}
		royalFlush = (straightFlush && startFlushStreak + longestFlushStreak == 13);
	}

	if (true)
	{
		// Print Cards
		for (int i = 0; i < 13; i++)
		{
			cout << "{ ";
			for (int j = 0; j < 4; j++)
				cout << orderedCards[i][j] << " ";
			cout << "} { " << orderedCardsCombined[i] << " } " << endl;
		}
	}

	if (royalFlush)
		return ROYAL_FLUSH;

	if (straightFlush)
		return STRAIGHT_FLUSH;

	for (int i = 0; i < 13; i++) {
		if (orderedCardsCombined[i] == 4)
			return FOUR_OF_KIND;
	}

	int pairs = 0;
	for (int i = 0; i < 13; i++)
	{
		if (orderedCardsCombined[i] == 2)
			pairs++;
	}

	int trips = 0;
	for (int i = 0; i < 13; i++)
	{
		if (orderedCardsCombined[i] == 3)
			trips++;
	}

	if (trips > 0 && pairs > 0)
		return FULL_HOUSE;

	{
		int suitCount[4] = {};

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 4; j++)
				suitCount[j] += orderedCards[i][j];
		}

		for (int i = 0; i < 4; i++)
		{
			if (suitCount[i] >= 5)
				return FLUSH;
		}
	}

	if (straight)
		return STRAIGHT;

	if (trips > 0)
		return THREE_OF_KIND;

	if (pairs > 1)
		return TWO_PAIR;

	if (pairs == 1)
		return PAIR;

	return HIGH_CARD;
}

int main()
{
	Deck deck;

	Card cards[7];
	int counter = 0;
	while (!GetAsyncKeyState(VK_F1))
	{
		for (int i = 0; i < 7; i++)
			cards[i] = deck.drawCard();
		if (evaluateHand(cards, 7) == FLUSH)
			break;
		cout << ++counter;
		cout << endl;
	}

	return 0;
}
