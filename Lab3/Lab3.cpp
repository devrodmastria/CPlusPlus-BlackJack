// Program name: Lab 3 - BlackJack : game of cards
// Programmer: Rod Mesquita
// Date: 11/23/2018
// Honor code: I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.

#include "pch.h"
#include <iostream>
#include <ctime>
#include <vector> // no need to determine size at definition
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

		... and much more.

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
int main();

void gotoxy(int h, int w) {

	HANDLE hConsolse = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsolse) {
		COORD pos = { h, w };
		SetConsoleCursorPosition(hConsolse, pos);
	}
	return;
}

void printHeader() {

	cout << " Dealer" << setw(9);

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

	if (rank == -1)
		return "  ";

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
	
	if (suit == -1)
		return " ";

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

	// Below are some of my failed attempts to display the icons for the suits using Unicode.
	//const char *spades = u8"\u2664";
	//printf("\x2665\n");
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

void startRound() { //Deal two cards to each player
	

	//cout << "Deck size before: " << deck.size() << endl;

	// initialize players and dealer
	for (int x = 0; x < 8; x++) {

		// create 2 dimensional vector for players and their cards
		vector <int> newPlayer;
		players.push_back(newPlayer);

		// deal two cards per player
		// transfer card from deck to player
		players.at(x).push_back(deck[0]);
		deck.erase(deck.begin());
		players.at(x).push_back(deck[0]);
		deck.erase(deck.begin());

	}
	//cout << "Deck size after: " << deck.size() << endl;

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

bool winnerWinnerChickenDinner(int total, int player) {

	// for each player, if > 21, then lose
	// if == 21, then win

	gotoxy(0, 20);

	if (total > 21) {
		// Boo you lost it
		cout << "Player " << player << " lost the game :(                ";
		
		// SET value of 99 to player's card deck so that program can detect and exclude player from future rounds
		players[player][0] = 99;
		return false;
	}
	else if (total == 21) {
		// Whoop Whoop! Winner winner chicken dinner!
		cout << "Player " << player << " -> Winner Winner Chicken Dinner!" << endl;
		return true;
	}
}

void updateTotal() {

	vector <int> playerTotal(8);

	bool chickenDinner = false;

	// calculate total for each active player
	for (int playerIndex = 0; playerIndex < 8; playerIndex++) {

		if (players[playerIndex][0] != 99) {

			int cardsQty = players[playerIndex].size();

			int cardIndex = 0;

			while (cardIndex < cardsQty) {

				int cardIs = indexToCard(players[playerIndex][cardIndex]);

				if (cardIs > 10) {
					playerTotal[playerIndex] += 10;
					chickenDinner = winnerWinnerChickenDinner(playerTotal[playerIndex], playerIndex);
				}
				else {
					playerTotal[playerIndex] += cardIs;
					chickenDinner = winnerWinnerChickenDinner(playerTotal[playerIndex], playerIndex);
				}

				cardIndex++;

			}
		}
	}

	// display totals only for active players
	for (int playerIndex = 1; playerIndex < 8; playerIndex++) {
		gotoxy((playerIndex * 12), 15);
		if (players[playerIndex][0] != 99) {
			cout << playerTotal[playerIndex];
		}
		else { // players who lost go here
			cout << " X ";
		}
	}

	gotoxy((8*12), 15);
	cout << "totals" << endl;

	// Solution to bonus question: start over without restarting program
	//if (chickenDinner) {
	//	char startAgain = 'n';
	//	gotoxy(0,21);
	//	cout << "Start new game? (y/n)";
	//	cin >> startAgain;
	//	if (startAgain == 'y') {
	//		// STOP game and ask to start over
	//		// clear vectors, clear screen, call main()

	//		currentPlayer = 1;
	//		roundIs = 1;
	//		//deck.clear();
	//		//players.clear();
	//		system("cls");
	//		main();

	//	}
	//}

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

void initializeNextRound() {
	// create placeholder cards for each player
	for (int i = 0; i < 8; i++) {
		players.at(i).push_back(-1);
	}
}

int anotherCard(bool getNewCard) {

	if (getNewCard) {

		// transfer card from deck to player
		players.at(currentPlayer).push_back(deck[0]);
		deck.erase(deck.begin());

		// display new card
		for (int i = 0; i < 8; i++) {

			gotoxy(getX(i), (roundIs + 3));

			int x = i;
			int y = players[i].size() - 1;

			cout << getSuit(players[x][y]) << getRank(players[x][y]);

		}

		cout << endl;
		// end of display new card

	}

	for (int i = 1; i < 8; i++) {

		if ((currentPlayer + i) < players.size()) {
			if (players[currentPlayer + i][0] != 99) {
				currentPlayer += i;
				break;
			}
		}
		else {

			for (int i = 1; i < 8; i++) {
			
				if (players[i][0] != 99) {
					currentPlayer = i;
					break;
				}
			
			}
		}
	}

	if (currentPlayer == 7) {
		roundIs += 1;
		initializeNextRound();
	} 

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

	initializeNextRound();

	do {

		updateTotal();

		gotoxy(0, 17);
		cout << "Another card for player " << currentPlayer << "? (y/n)" << endl;
		cin >> getNewCard;
		gotoxy(0, 0);
		cout << " ";

		if (getNewCard == 'y')
			anotherCard(true);
		else if (getNewCard == 'n')
			anotherCard(false);

	} while (getNewCard == 'y' || getNewCard == 'n');
	
	return 0;
}
