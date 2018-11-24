// Program name: Lab 3 - BlackJack : game of cards
// Programmer: Rod Mesquita
// Date: 11/23/2018
// Honor code: I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.

#include "pch.h"
#include <iostream>
#include <ctime>
#include <vector> // no need to determinze size at definition

using namespace std;

/*

	Self-thought Directions:
	
		7 players, one dealer

		Use random number generator with output ranging from 0 through 12, then match with Ace thru King, respective, then assign card to player

		Prompt user after each round (refer to previous homeworks)

		If player's total exceeds 21, player is out.

		Dealer gets card last - when his cards add up to at least 17, end round.

	Tools needed: 
		
		Random number generator - answer: Random Number Generation Examples.pdf from Canvas

		Loop to prompt user for input

		Special characters?

*/

void displayRank(int rank) {
	if (rank == 0)
		cout << " Ace of ";
	else if (rank == 10)
		cout << "Jack of ";
	else if (rank == 11)
		cout << "Queen of ";
	else if (rank == 12)
		cout << "King of ";
	else
		cout << rank << "  of ";
}

void displaySuit(int suit) {

	if (suit == 0)
		cout << " Clubs" << endl;
	else if (suit == 1)
		cout << "Diamonds" << endl;
	else if (suit == 2)
		cout << "Hearts" << endl;
	else if (suit == 3)
		cout << "Spades" << endl;

}

int main()
{
	vector<int> playerDecks;
	vector<int> mainDeck(52);

	// Initialize cards - 0-12 Clubs / 13-25 Diamonds / 26-38 Hearts / 39-51 Spades
	for (int i = 0; i < 52; i++) {

		mainDeck[i] = i;

	}

	// Shuffle cards
	srand(time(0));
	for (int i = 0; i < 52; i++) {

		int index = rand() % 52;
		int temp = mainDeck[i];
		mainDeck[i] = mainDeck[index];
		mainDeck[index] = temp;

	}

	// Display first four cards
	for (int i = 0; i < 4; i++) {
		displayRank(mainDeck[i] % 13);
		displaySuit(mainDeck[i] / 13);
	}

	return 0;
}
