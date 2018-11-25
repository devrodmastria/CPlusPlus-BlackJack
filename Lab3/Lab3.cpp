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

vector<int> deck(52);
vector<int> dealer;
vector<int> playerOne;
vector<int> playerTwo;
vector<int> playerThree;
vector<int> playerFour;
vector<int> playerFive;
vector<int> playerSix;
vector<int> playerSeven;

vector<vector<int>> players;

string getRank(int);
string getSuit(int);
void printHeader();
void startRound();

string getRank(int rank) {

	int rawRank = rank;

	rank %= 13;

	string rankIs;

	if (rank == 0)
		rankIs = "A";
	else if (rank == 10)
		rankIs = "J";
	else if (rank == 11)
		rankIs = "Q";
	else if (rank == 12)
		rankIs = "K";
	else
		rankIs = to_string(rank);

	return rankIs;
}

string getSuit(int suit) {

	suit /= 13;

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

void printHeader() {

	cout << "dlr";
	for (int i = 1; i < 8; i++) {
		cout << setw(6) << i;
	}

	cout << endl;
	for (int i = 0; i < 8; i++) {
		if (i < 7)
			cout << "---" << setw(6);
		else
			cout << "---";
	}
	cout << endl;

}

//Deal two cards to each player
void startRound() {

	// initialize players and dealer
	for (int x = 0; x < 8; x++) {

		vector <int> newPlayer;
		players.push_back(newPlayer);
		players.at(x).push_back(deck[x]);

	}

	//// Display cards dealt
	//for (int i = 0; i < 8; i++) {

	//	if (i < 7)
	//		cout << players[i][0] << setw(6);
	//	else
	//		cout << players[i][0];
	//}

	//cout << endl;


	// Display cards dealt
	for (int i = 0; i < 8; i++) {

		if (i < 7)
			cout << getSuit(players[i][0]) << getRank(players[i][0]) << setw(5);
		else
			cout << getSuit(players[i][0]) << getRank(players[i][0]);
	}

		//getRank(deck[i]);
		//getSuit(deck[i]);
}

int main()
{

	char again;

	printHeader();

	// Initialize cards - 0-12 Clubs / 13-25 Diamonds / 26-38 Hearts / 39-51 Spades
	for (int i = 0; i < 52; i++) {

		deck[i] = i;

	}

	// Shuffle cards
	srand(time(NULL));
	for (int i = 0; i < 52; i++) {

		int index = rand() % 52;
		int temp = deck[i];
		deck[i] = deck[index];
		deck[index] = temp;

	}

	startRound();

	do {

		cout << endl;


		cout << "\nPlay again? (y/n)" << endl;
		cin >> again;

	} while (again == 'y' || again == 'Y');
	
	return 0;
}
