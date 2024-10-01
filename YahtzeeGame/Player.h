#pragma once

#include "stdafx.h"
#include "Scorecard.h"
#include "Combinations.h"

class Player {
public:
	Player(int p_id);
	Player();
	~Player();


	// All the dice functions
	void playRoll();
	vector<int> diceIndex(int dice_to_reroll); // returns vector of indices with the given number
	void displayDice();


protected:

	int player_id; // 1 for human, 2 for computer

	const int max_rolls = 3;
	int num_rolls;
	int num_of_dice;
	char player_choice = ' ';

	vector<int> dice;

	
	vector<int> combinations; // to store the available unsocred categories as per the dice 

	//Combinations board;

	

};