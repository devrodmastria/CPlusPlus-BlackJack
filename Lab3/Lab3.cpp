// Program name: Lab 3 - BlackJack : game of cards
// Programmer: Rod Mesquita
// Date: 11/23/2018
// Honor code: I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.

#include "pch.h"
#include <iostream>
#include <ctime>
#include <vector> // no need to determinze size at definition
#include <stdio.h>
#include <iomanip>
#include <string>
#include <windows.h>

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

int currentPlayer = 1;
int roundIs = 1;

vector<int> deck(52);
vector<vector<int>> players;

string getRank(int);
string getSuit(int);
void printHeader();
void startRound();
void updateTotal();

void gotoxy(int h, int w) {

	HANDLE hConsolse = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsolse) {
		COORD pos = { h, w };
		SetConsoleCursorPosition(hConsolse, pos);
	}
	return;
}

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

	//cout << "Deck size before: " << deck.size() << endl;

	// initialize players and dealer
	for (int x = 0; x < 8; x++) {

		vector <int> newPlayer;
		players.push_back(newPlayer);

		// deal two cards per player
		players.at(x).push_back(deck[0]);
		deck.erase(deck.begin());
		players.at(x).push_back(deck[0]);
		deck.erase(deck.begin());

	}
	//cout << "Deck size after: " << deck.size() << endl;


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

	vector <int> playerTotal(8);
	//const char *spades = u8"\u2664";
	//cout << " Player one card quantity: " << players[1].size() << endl;
	//printf("\x2665\n");

	//Display total for each player
	for (int x = 0; x < 8; x++) { // first round

		int cardsQty = players[x].size();

		int cardIndex = 0;

		while (cardIndex < cardsQty) {

			int cardIs = indexToCard(players[x][cardIndex]);

			if (cardIs > 10) {
				playerTotal[x] += 10;
			}
			else
				playerTotal[x] += cardIs;

			cardIndex++;

		}

	}

	gotoxy(0, 15);
	cout << setw(14) 
		<< playerTotal[1] << setw(12)
		<< playerTotal[2] << setw(12)
		<< playerTotal[3] << setw(12)
		<< playerTotal[4] << setw(12)
		<< playerTotal[5] << setw(12)
		<< playerTotal[6] << setw(12)
		<< playerTotal[7] << setw(12)
		<< "totals" << endl;

}

int getX(int i) {
	int xIs = 0;

	switch (i) {
		case 0:
			xIs = 0;
			break;
		case 1:
			xIs = 12;
			break;
		case 2:
			xIs = 24;
			break;
		case 3:
			xIs = 36;
			break;
		case 4:
			xIs = 48;
			break;
		case 5: 
			xIs = 60;
			break;
		case 6:
			xIs = 72;
			break;
		case 7:
			xIs = 84;
			break;
		deafult:
			xIs = 96;
			break;
	}

	//cout << "getX:" << xIs << endl;

	return xIs;
}

int anotherCard(bool getNewCard) {

	if (getNewCard) {
		players.at(currentPlayer).push_back(deck[0]);
		deck.erase(deck.begin());

		// display new card
		for (int i = 0; i < 8; i++) {

			gotoxy(getX(i), (roundIs + 4));

			if (i == currentPlayer){
				cout << getSuit(players[i][players[i].size() - 1]) << getRank(players[i][players[i].size() - 1]);
			}
			else {
				cout << "      ";
			}

		}

		cout << endl;
		// end of display new card

		if (currentPlayer == 7) {
			currentPlayer = 1;
			roundIs += 1;
		}
		else
			currentPlayer += 1;

	}
	else if (currentPlayer == 7) {
		currentPlayer = 1;
		roundIs += 1;
	}
	else
		currentPlayer += 1;

	return currentPlayer;
}

int main()
{

	char getNewCard = 'n';

	printHeader();

	// Initialize cards - 0-12 Clubs / 13-25 Diamonds / 26-38 Hearts / 39-51 Spades
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
		deck[i] = i;
	
	// Shuffle cards
	srand(time(NULL));
	for (int i = 0; i < NUMBER_OF_CARDS; i++) {

		int index = rand() % NUMBER_OF_CARDS;
		int temp = deck[i];
		deck[i] = deck[index];
		deck[index] = temp;

	}

	startRound();

	do {

		updateTotal();

		cout << "Another card for player " << currentPlayer << "? (y/n)" << endl;
		cin >> getNewCard;

		if (getNewCard == 'y')
			anotherCard(true);
		else if (getNewCard == 'n')
			anotherCard(false);

	} while (getNewCard == 'y' || getNewCard == 'n');
	
	return 0;
}
