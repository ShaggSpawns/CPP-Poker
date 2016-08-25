#include "Player.h"

std::string Player::getCards() {
	std::string temp = "[";
	for (int i = 0; i < numCards; ) {
		temp += hand[i++].getCard();
		if (numCards > i) temp += ", ";
	}
	temp += "]";
	return temp;
}

void Player::getNextSuit(int arr[4], int &currentSuit)
{
	if (currentSuit == -1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (arr[i] != 0) {
				currentSuit = i;
				return;
			}
		}
	}
	else
	{
		for (int i = currentSuit + 1; i < 4; i++)
		{
			if (arr[i] != 0) {
				currentSuit = i;
				return;
			}
		}
	}
	currentSuit = -1;
}

Hand Player::getHand(Card communityCards[5], int numCards)
{
	int orderedCards[13][4] = {};
	int orderedCardsCombined[13] = {};

	{
		Card temp;

		for (int i = 0; i < 2; i++)
		{
			temp = hand[i];
			orderedCards[temp.getRank()][temp.getSuit()] = 1;
			orderedCardsCombined[temp.getRank()]++;
		}

		for (int i = 2; i < numCards; i++)
		{
			temp = communityCards[i - 2];
			orderedCards[temp.getRank()][temp.getSuit()] = 1;
			orderedCardsCombined[temp.getRank()]++;
		}

		// Print Cards
		/*for (int i = 0; i < 13; i++)
		{
			std::cout << "{ ";
			for (int j = 0; j < 4; j++)
				std::cout << orderedCards[i][j] << " ";
			std::cout << "} { " << orderedCardsCombined[i] << " } " << std::endl;
		}*/
	}

	bool straight = false;
	bool aceExists = orderedCardsCombined[12] != 0;

	int highC = 0;

	{
		int streak = 0;

		for (int i = 0; i < 13; i++)
		{
			if (orderedCardsCombined[i] != 0)
			{
				streak++;
				highC = i;
			}
			else if (streak >= 5 || (streak == 4 && highC == 3 && aceExists))
			{
				straight = true;
				break;
			}
			else
			{
				streak = 0;
				highC = 0;
			}
		}
		if (!straight && streak >= 5)
			straight = true;
	}

	Rank sRankHandHigh;
	Suit fSuitHandHigh;

	bool flush;
	if (straight)
	{
		sRankHandHigh = (Rank)highC;

		int suitCheck = -1;

		for (int j = 0; j < orderedCardsCombined[highC]; j++)
		{
			flush = true;
			getNextSuit(orderedCards[highC], suitCheck);
			for (int i = highC; i > highC - 4; i--)
			{
				if (orderedCards[i][suitCheck] == 0)
				{
					flush = false;
					break;
				}
			}
			if (flush)
			{
				flush = ((aceExists && highC - 4 == 0) || (highC - 4 != 0)) && (orderedCards[highC - 4][suitCheck] == 1);
				if (flush) {
					fSuitHandHigh = (Suit)suitCheck;
					break;
				}
			}
		}

	}
	else
	{
		int suitCount[4] = {};
		flush = false;

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 4; j++)
				suitCount[j] += orderedCards[i][j];
		}

		for (int i = 0; i < 4; i++)
		{
			if (suitCount[i] >= 5)
			{
				flush = true;
				fSuitHandHigh = (Suit)i;
				break;
			}
		}
	}

	if (straight && flush) {
		suitHandHigh = fSuitHandHigh;
		rankHandHigh = sRankHandHigh;
		return (highC == Ace) ? ROYAL_FLUSH : STRAIGHT_FLUSH;
	}

	int quads = 0;

	for (int i = 0; i < 13; i++)
	{
		if (orderedCardsCombined[i] == 4) {
			rankHandHigh = (Rank)i;
			quads++;
		}
	}

	if (quads > 0)
		return FOUR_OF_KIND;

	int pairs = 0;
	Rank pairHigh;
	for (int i = 0; i < 13; i++)
	{
		if (orderedCardsCombined[i] == 2) {
			pairHigh = (Rank)i;
			pairs++;
		}
	}

	int trips = 0;
	Rank tripHigh;

	for (int i = 0; i < 13; i++)
	{
		if (orderedCardsCombined[i] == 3) {
			tripHigh = (Rank)i;
			trips++;
		}
	}

	if (trips > 0 && pairs > 0) {
		rankHandHigh = tripHigh;
		return FULL_HOUSE;
	}

	if (flush) {
		suitHandHigh = fSuitHandHigh;
		return FLUSH;
	}

	if (straight) {
		rankHandHigh = sRankHandHigh;
		return STRAIGHT;
	}

	if (trips > 0) {
		rankHandHigh = tripHigh;
		return THREE_OF_KIND;
	}

	if (pairs > 1) {
		rankHandHigh = pairHigh;
		return TWO_PAIR;
	}

	if (pairs == 1) {
		rankHandHigh = pairHigh;
		return PAIR;
	}

	int currentHigh = 0;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].getRank() > hand[currentHigh].getRank())
			currentHigh = i;
	}
	rankHandHigh = (Rank)currentHigh;
	return HIGH_CARD;
}
