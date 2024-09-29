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

	// genrate random number for five dice
	for (int i = 0; i < num_of_dice; i++) {
		dice[i] = ((rand() % 6) + 1);
	}

	cout << endl;
	// display the dice values
}


int Player::diceIndex(int dice_to_keep) {
	// find the index of the dice to keep
	for (int i = 0; i < num_of_dice; i++)
	{
		if (dice[i] == dice_to_keep)
		{
			return i;
		}
	}
	return -1;
}