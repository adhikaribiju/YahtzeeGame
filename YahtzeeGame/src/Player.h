#pragma once

#include "stdafx.h"
#include "Scorecard.h"
#include "Combinations.h"

class Player {
public:

	Player();
	Player(int p_id);
	virtual ~Player();

	// pure virtual function to play a turn
	virtual void playTurn() = 0;

	// All the dice functions
	void playRoll();
	vector<int> diceIndex(int dice_to_reroll); // returns vector of indices with the given number
	void displayDice();



protected:

	// to store the maximum number of rolls allowed
	const int MAX_ROLLS = 3;
	// to store the number of dice in the game
	const int DICE_COUNT = 5;

	// 1 for human, 2 for computer
	int player_id;
	// to store the number of rolls
	int num_rolls;
	// to store the player's choice
	char player_choice;

	// to store the dice values
	vector<int> dice;

	// to store the available unsocred categories as per the dice 
	vector<int> combinations;
};