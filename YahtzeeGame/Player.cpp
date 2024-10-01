#include "Player.h"

Player::Player() {

	player_id = 0; // 1 for human, 2 for computer

	num_rolls = 1;
	num_of_dice = 5;

	// initialing the dice vector
	for (int i = 0; i < num_of_dice; i++)
	{
		dice.push_back(0);
	}
	
}

Player::Player(int p_id) {


	player_id = p_id; // 1 for human, 2 for computer
	
	num_rolls = 1;
	num_of_dice = 5;


}


Player::~Player() {



}

void Player::displayDice() {
	cout << "Dice: ";
	for (int i = 0; i < num_of_dice; i++) {
		cout << dice[i] << " ";
	}
	cout << endl;
}

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
			for (int i = 0; i < num_of_dice; i++) {
				do {
					cout << "Enter the value for dice " << i + 1 << " : ";
					cin >> dice[i];
					if (dice[i] < 1 && dice[i]> 6)
					{
						cout << "Invalid entry! Enter values from 1-6 " << endl;
					}
				} while (dice[i] < 1 && dice[i]> 6);
			}
		}
		else if (choice == "N" || choice == "n")
		{
			cout << "Rolling the dice randomly..." << endl;
			// genrate random number for five dice
			for (int i = 0; i < num_of_dice; i++) {
				dice[i] = ((rand() % 6) + 1);
			}
		}
		else
		{
			cout << "Invalid entry! Enter Y or N " << endl;
		}
	} while (choice != "N" && choice != "n" && choice != "Y" && choice != "y");


}


vector<int> Player::diceIndex(int dice_to_reroll) {
	vector<int> recordIndices;
	// find the index of the dice to keep
	for (int i = 0; i < num_of_dice; i++)
	{
		if (dice[i] == dice_to_reroll)
		{
			recordIndices.push_back(i);
		}
	}
	return recordIndices;
}

