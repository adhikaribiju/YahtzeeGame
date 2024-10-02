#include "Player.h"

Player::Player() {

	player_id = 0; // 1 for human, 2 for computer

	num_rolls = 1;
	player_choice = ' ';

	// initialing the dice vector
	for (int i = 0; i < DICE_COUNT; i++)
	{
		dice.push_back(0);
	}
}

Player::Player(int p_id) {

	player_id = p_id; // 1 for human, 2 for computer
	num_rolls = 1;
	player_choice = ' ';
}


Player::~Player() {
}

/* *********************************************************************
Function Name: displayDice
Purpose: To display the dice values
Parameters:
	None
Return Value:
	None
Algorithm:
	1. Display the dice values in the dice array
Reference: None
********************************************************************* */
void Player::displayDice() {
	cout << "Dice: ";
	for (int i = 0; i < DICE_COUNT; i++) {
		cout << dice[i] << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: playRoll
Purpose: To roll the dice
Parameters:
	None
Return Value:
	None
Algorithm:
	1. Ask the user if they want to manually input the dice values
	2. If yes, take the input from the user
	3. If no, generate random numbers for the dice
Reference: None
********************************************************************* */
void Player::playRoll() {
	// A roll consists of rolling 5 dice

	srand((unsigned)time(0));

	string choice = " ";
	cin.ignore();

	do {
		cout << "Do you wish to manually input all dices? (Y/N)" << endl;
		getline(cin, choice);

		if (choice == "Y" || choice == "y")
		{
			for (int i = 0; i < DICE_COUNT; i++) {
				do {
					cout << "Enter the value for dice " << i + 1 << " : ";
					cin >> dice[i];
					if (dice[i] < 1 || dice[i]> 6)
					{
						cout << "Invalid entry! Enter values from 1-6 " << endl;
					}
				} while (dice[i] < 1 || dice[i]> 6);
			}
		}
		else if (choice == "N" || choice == "n")
		{
			cout << "Rolling the dice randomly..." << endl;
			// genrate random number for five dice
			for (int i = 0; i < DICE_COUNT; i++) {
				dice[i] = ((rand() % 6) + 1);
			}
		}
		else
		{
			cout << "Invalid entry! Enter Y or N " << endl;
		}
	} while (choice != "N" && choice != "n" && choice != "Y" && choice != "y");


}

/* *********************************************************************
Function Name: diceIndex
Purpose: To find the index of the dice to keep
Parameters:
	dice_to_reroll, an integer
Return Value:
	vector<int>, a vector of integers
Algorithm:
	1. Find the index of the dice to keep
	2. Return the vector of indices
Reference: None
********************************************************************* */
vector<int> Player::diceIndex(int dice_to_reroll) {
	vector<int> recordIndices;
	// find the index of the dice to keep
	for (int i = 0; i < DICE_COUNT; i++)
	{
		if (dice[i] == dice_to_reroll)
		{
			recordIndices.push_back(i);
		}
	}
	return recordIndices;
}

