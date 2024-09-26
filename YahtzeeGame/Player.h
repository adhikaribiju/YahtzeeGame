#pragma once

#include "stdafx.h"
#include "Scorecard.h"

class Player {
public:
	Player();
	~Player();

	//????void setScore(int score);


	int diceIndex(int dice_to_keep);
	void DisplayDice();


private:
	const int max_rolls = 3;
	int num_rolls;
	int num_of_dice;

	vector<int> dice;

};