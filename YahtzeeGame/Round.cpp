#include "Round.h"
using namespace std;

int Round::numOfRounds = 1;

Round::Round() {

	player_id = 0;
	player_choice = ' ';
	num_rolls = 1;

	// initializing the dice values to 0
	for (int i = 0; i < NUM_OF_DICE; i++) {
		dice.push_back(0);
	}
}


Round::~Round() {
	dice.clear();
}

void Round::playRound(int player_id) {
	// A turn consists of maximun of 3 rolls

	Human human; //s create a human object
	Computer computer; // create a computer object


	cout << "\nRound " << numOfRounds << endl;



	if (player_id == 1) {
		human.playTurn();
		computer.playTurn();
	}
	else
	{
		computer.playTurn();
		human.playTurn();
	}

	if (isSaveGame()) {
		Serialization serialize;
		if (serialize.saveGame()) {
			cout << "Game saved!" << endl;
			exit(0); // Exit the program
		}
	}

	numOfRounds++;
}

int Round::diceIndex(int dice_to_keep) {
	// find the index of the dice to keep
	for (int i = 0; i < NUM_OF_DICE; i++)
	{
		if (dice[i] == dice_to_keep)
		{
			return i;
		}
	}
	return -1;
}


void Round::displayDice() {
	// display the dice values
	for (int i = 0; i < NUM_OF_DICE; i++)
	{
		cout << "Dice " << i + 1 << ": " << dice[i] << endl;
	}
	cout << endl;
}


const int Round::getRoundNo() {
	return numOfRounds;
}

bool Round::isSaveGame() {

	string save_game;

	// Keep asking until a valid response is provided
	do {
		cout << "Do you wish to save the game? (Y/N): ";
		cin >> save_game;

		// Check if the input is exactly one character
		if (save_game.length() == 1) {
			char answer = tolower(save_game[0]); // Convert to lowercase for uniformity

			// Validate the response
			if (answer == 'y') {
				cout << "Saving now..." << endl;
				return true;
			}
			else if (answer == 'n') {
				return false;
			}
		}

		// If the input is not valid, show an error and loop again
		cout << "Invalid input. Please enter Y/N only." << endl;

	} while (true); // Loop until a valid response is given
}

