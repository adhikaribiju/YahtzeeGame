#pragma once

#include "stdafx.h"
#include "Player.h"

class Computer : public Player {

public:
	Computer();
	~Computer();

	void playTurn();
	void findCategoryScore(); // find the category available on the dice and its corresponding score


	// Functions for computer strategy
	bool computerDecide(); // to decide if computer should keep rolling or score
	bool lowerSectionFilled(); // to check if lower section is left to score
	void scoreHighestAvailable(); // score the highest points availble currently
	bool isSequentialAvailable(); // if sequential possible by rolling dice, it rolls them and returns true
	void tryYahtzeeOrFullHouse(); // function to roll certain dices to get Yathzee or Full House

private:

	int num_rolls; // to track the number of rolls played

	bool reroll;
	bool keepError;
	bool isScoreSet; // to check if the score has been set

	vector<pair<int, int>> scoresAvailable;
	vector<int> keptDices; // to track the indices of the dice kept and NOT Rolled
	vector<int> availableCategory; // stores the matching categories based on the dice 
	// Note: The above vector doesn't check if that category is already filled in the scorecard

	Combinations board; // retrive the combinations
	 
};
