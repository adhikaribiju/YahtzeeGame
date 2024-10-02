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

/* *********************************************************************
Function Name: playRound
Purpose: To start a round consisting of two turns
Parameters:
	player_id, an integer
		1 for human, 2 for computer
Return Value:
	None
Algorithm:
	1. Create a Human object
	2. Create a Computer object
	3. Display the round number
	4. If the player is human, let the human play the turn first
	5. If the player is computer, let the computer play the turn first
	6. If the player decides to save the game, save the game and exit
	7. Increment the number of rounds played
Reference: None
********************************************************************* */
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

/* *********************************************************************
Function Name: resumeRound
Purpose: To resume a round consisting of two turns
Parameters:
	player_id, an integer
		1 for human, 2 for computer
Return Value:
	None
Algorithm:
	1. Create a Human object
	2. Create a Computer object
	3. Display the round number
	4. If the player is human, let the human play the turn first
	5. If the player is computer, let the computer play the turn first
	6. If the player decides to save the game, save the game and exit
	7. Increment the number of rounds played
Reference: None
********************************************************************* */
void Round::resumeRound(int player_id) {


	Human human; //s create a human object
	Computer computer; // create a computer object
	Combinations c;

	cout << "\nRound " << numOfRounds << endl;

	if (player_id == 1) {
		human.playTurn();
		if (!c.isScorecardFull()) computer.playTurn();
	}
	else
	{
		computer.playTurn();
		if (!c.isScorecardFull()) human.playTurn();
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

/* *********************************************************************
Function Name: diceIndex
Purpose: To find the index of the dice to keep
Parameters:
	dice_to_keep, an integer
		the value of the dice to keep
Return Value:
	the index of the dice to keep
Algorithm:
	1. Find the index of the dice to keep
	2. Return the index
Reference: None
********************************************************************* */
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

/* *********************************************************************
Function Name: displayDice
Purpose: To display the dice values
Parameters:
	None
Return Value:
	None
Algorithm:
	1. Iterate through the dice array
	2. Display the dice values
Reference: None
********************************************************************* */
void Round::displayDice() {
	// display the dice values
	for (int i = 0; i < NUM_OF_DICE; i++)
	{
		cout << "Dice " << i + 1 << ": " << dice[i] << endl;
	}
	cout << endl;
}

/* *********************************************************************
Function Name: getRoundNo
Purpose: getter function to return the number of rounds played
Parameters:
	None
Return Value:
	int, the number of rounds played
Reference: None
********************************************************************* */
const int Round::getRoundNo() {
	return numOfRounds;
}

/* *********************************************************************
Function Name: isSaveGame
Purpose: To check if the user wants to save the game
Parameters:
	None
Return Value:
	'true' if the user wants to save the game, 'false' otherwise
Algorithm:
	1. Ask the user if they want to save the game
	2. If the user wants to save the game, return 'true'
	3. Otherwise, return 'false'
Reference: None
********************************************************************* */
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

