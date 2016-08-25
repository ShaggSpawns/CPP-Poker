#include "Board.h"

void debugProbability(Hand h, int tries)
{
	Board d = Board();
	d.shuffle();

	std::string hands[10] = { "High Card", "Pair", "Two Pair", "Three", "Sraight", "Flush", "Full House", "Four", "Sraight Flush", "Royal Flush" };

	Player player = Player("DEBUG");
	Card cards[5];
	Hand hand;
	int count = -1;

	do
	{
		for (int i = 0; i < 5; i++)
			cards[i] = d.drawCard();
		player.setCards(d.drawCard(), d.drawCard());
		hand = player.getHand(cards, 5);
		std::cout << ++count << " " << hands[hand] << std::endl;
	}
	while (count < tries && hand != h);
}

void testHands()
{
	Board d = Board();
	d.shuffle();

	std::string hands[10] = { "High Card", "Pair", "Two Pair", "Three", "Sraight", "Flush", "Full House", "Four", "Sraight Flush", "Royal Flush" };

	Player player = Player("DEBUG");
	Card cards[5] = { Card(Nine, Heart), Card(King, Diamond), Card(Queen, Spade), Card(Jack, Heart), Card(Ten, Heart) };
	Hand hand;

	player.setCards(Card(Three, Heart), Card(King, Heart));
	hand = player.getHand(cards, 5);
	std::cout << hands[hand] << std::endl;
}



int mainGame()
{
	using namespace std;

	bool playing = true;
	int numPlayers = 2;
	std::string hands[10] = { "High Card", "Pair", "Two Pair", "Three", "Sraight", "Flush", "Full House", "Four", "Sraight Flush", "Royal Flush" };

	Board board;

	string input;
	for (int i = 0; i < numPlayers; i++)
	{
		cout << "Enter Player: ";
		getline(cin, input);
		board.addPlayer(Player(input));
	}
	system("cls");

	Card tempCards[5] = {};
	do
	{
		board.dealAll();
		board.addCommunityCards();
		//preflop (bet)
		//flop (flip 3 cards)
		system("cls");
		board.showCards(3);
		tempCards[0] = board.getCard(0);
		tempCards[1] = board.getCard(1);
		tempCards[2] = board.getCard(2);
		cout << "\n";
		cout << board.getPlayer(0).getCards() << " " << hands[board.getPlayer(0).getHand(tempCards, 3)];
		cin.get();
		//turn (flip 4th)
		system("cls");
		board.showCards(4);
		tempCards[3] = board.getCard(3);
		cout << "\n";
		cout << board.getPlayer(0).getCards() << " " << hands[board.getPlayer(0).getHand(tempCards, 4)];
		cin.get();
		//river (flip 5th / final)
		system("cls");
		board.showCards(5);
		tempCards[4] = board.getCard(4);
		cout << "\n";
		cout << board.getPlayer(0).getCards() << " " << hands[board.getPlayer(0).getHand(tempCards, 5)];
		cin.get();
		//showdown (show cards)
		system("cls");
		board.printBoard();

		//system("cls");
		cout << "Play again? (Y/N): ";
		getline(cin, input);
		//playing = input == "Y";
		system("cls");
		playing = true;
		board.clear();
	}
	while (playing);

	return EXIT_SUCCESS;
}