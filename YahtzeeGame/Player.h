#pragma once

#include "stdafx.h"
#include "Scorecard.h"
#include "Combinations.h"

class Player {
public:

	Player();
	Player(int p_id);
	~Player();


	// All the dice functions
	void playRoll();
	vector<int> diceIndex(int dice_to_reroll); // returns vector of indices with the given number
	void displayDice();


protected:
	const int MAX_ROLLS = 3;
	const int DICE_COUNT = 5;

	int player_id; // 1 for human, 2 for computer
	int num_rolls;
	char player_choice;

	vector<int> dice;
	vector<int> combinations; // to store the available unsocred categories as per the dice 

};