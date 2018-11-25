// Program name: Lab 3 - BlackJack : game of cards
// Programmer: Rod Mesquita
// Date: 11/23/2018
// Honor code: I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.

#include "pch.h"
#include <iostream>
#include <ctime>
#include <vector> // no need to determinze size at definition
#include <clocale> // to display cards symbols
#include <stdio.h>
#include <iomanip>
#include <string>

using namespace std;

/*

	Self-thought Directions:
	
		7 players, one dealer

		Use random number generator with output ranging from 0 through 12, then match with Ace thru King, respective, then assign card to player

		Prompt user after each round (refer to previous homeworks)

		If player's total exceeds 21, player is out.

		Dealer gets card last - when his cards add up to at least 17, end round.

	Tools needed: 
		
		Random number generator - answer: Random Number Generation Examples.pdf from Canvas OK

		Do-while loop to prompt user for input OK

		Special characters NOPE

*/

const int NUMBER_OF_CARDS = 52;

vector<int> deck(52);
vector<vector<int>> players;

string getRank(int);
string getSuit(int);
void printHeader();
void startRound();
void updateTotal();

void printHeader() {

	cout << "Dealer " << setw(10);

	for (int i = 1; i < 8; i++) {
		cout << setw(11) << "Player" << i;
	}

	cout << endl;
	for (int i = 0; i < 8; i++) {
		if (i < 7)
			cout << "-------" << setw(12);
		else
			cout << "-------";
	}
	cout << endl;

}

int indexToCard(int index) {
	int cardIs = ((index % 13) + 1);
	return cardIs;
}

string getRank(int rank) {

	int rankMOD13 = rank % 13; // card index MOD 13

	string rankIs;

	if (rankMOD13 == 0)
		rankIs = "A "; // added space to make it look good with cards with rank of 10
	else if (rankMOD13 == 10)
		rankIs = "J ";
	else if (rankMOD13 == 11)
		rankIs = "Q ";
	else if (rankMOD13 == 12)
		rankIs = "K ";

	else if (rankMOD13 == 9)
		rankIs = to_string(rankMOD13 + 1);
	else
		rankIs = to_string(rankMOD13 + 1) + " ";

	//cout << endl << "Rank is " << rank << "| Rank % 13 is " << (rank % 13) << " so rank is " << rankIs << endl;

	return rankIs;
}

string getSuit(int suit) {

	suit /= 13; // card index DIVIDED by 13

	string suitIs;
	if (suit == 0)
		suitIs = "C";
	else if (suit == 1)
		suitIs = "D";
	else if (suit == 2)
		suitIs = "H";
	else if (suit == 3)
		suitIs = "S";

	//if (suit == 0)
	//	cout << "Clubs \u2667" << endl;
	//else if (suit == 1)
	//	cout << "Diamonds \u2662" << endl;
	//else if (suit == 2)
	//	cout << "Hearts \u2661" << endl;
	//else if (suit == 3)
	//	cout << "Spades \u2664" << endl;

	return suitIs;

}

//Deal two cards to each player
void startRound() {

	// initialize players and dealer
	for (int x = 0; x < 8; x++) {

		vector <int> newPlayer;
		players.push_back(newPlayer);

		// deal two cards per player
		players.at(x).push_back(deck[x]);
		players.at(x).push_back(deck[x + 8]);

		//cout << "deck[x] " << setw(3) << deck[x] << " deck[x + 8] " << setw(3) << deck[x + 8] << " deck[0] " << deck[0] << " deck[51] " << deck[51] << endl;
	}

	cout << endl;

	// Display cards dealt
	for (int i = 0; i < 8; i++) {
		if (i == 0) // hide first player's card
			cout << " ? " << setw(10); // added spaces to make it look good with cards with rank of 10
		else if (i < 7)
			cout << getSuit(players[i][0]) << getRank(players[i][0]) << setw(10);
		else
			cout << getSuit(players[i][0]) << getRank(players[i][0]);
	}	
	cout << endl;

	for (int i = 0; i < 8; i++) {
		if (i < 7)
			cout << getSuit(players[i][1]) << getRank(players[i][1]) << setw(10);
		else
			cout << getSuit(players[i][1]) << getRank(players[i][1]);
	}
	cout << endl;

}

void updateTotal() {

	cout << endl << endl;

	int sumIs = 0;

	//Display total for a player
	for (int y = 0; y < 2; y++) {

		int rawCard = players[1][y];
		int cardIs = indexToCard(players[1][y]);

		if (cardIs > 10) {
			sumIs += 10;
			cardIs = 10;
		}
		else 
			sumIs += cardIs;

		//cout << "Player 1 card index " << rawCard << endl;
		//cout << "Player 1 card value " << cardIs << endl;

		cout << endl;

	}

	cout << setw(13) << sumIs << setw(80) << "totals" << endl;

}

int main()
{

	char again;

	printHeader();

	// Initialize cards - 0-12 Clubs / 13-25 Diamonds / 26-38 Hearts / 39-51 Spades
	for (int i = 0; i < NUMBER_OF_CARDS; i++) {

		deck[i] = i;

	}

	// Shuffle cards
	srand(time(NULL));
	for (int i = 0; i < NUMBER_OF_CARDS; i++) {

		int index = rand() % NUMBER_OF_CARDS;
		int temp = deck[i];
		deck[i] = deck[index];
		deck[index] = temp;

	}

	startRound();

	updateTotal();

	do {

		cout << endl;
		cout << "\nPlay again? (y/n)" << endl;
		cin >> again;

	} while (again == 'y' || again == 'Y');
	
	return 0;
}
