#pragma once

#include "stdafx.h"
#include "Player.h"

class Computer : public Player {

public:
	Computer();
	~Computer();

	// to play the turn for the computer
	void playTurn() override; 
	// find the category available on the dice and its corresponding score
	void findCategoryScore();


	// Functions for computer strategy
	// to decide if computer should keep rolling or score
	bool computerDecide(); 
	// to check if lower section is left to score
	bool lowerSectionFilled();
	// score the highest points availble currently
	void scoreHighestAvailable(); 
	// if sequential possible by rolling dice, it rolls them and returns true
	bool isSequentialAvailable();
	// function to roll certain dices to get Yathzee or Full House
	void tryYahtzeeOrFullHouse(); 

	// ask if the user wants to input the dice manually
	int askifInputManual(int dice_no);

private:

	// to track the number of rolls played by the computer
	int num_rolls;

	// to track whether the computer wants to reroll the dice
	bool reroll;

	// flag to check if the computer gets a conflct in the dice reroll
	bool keepError;
	// to check if the score has been set
	bool isScoreSet;

	// to store the scores available on the dice
	vector<pair<int, int>> scoresAvailable;

	// to track the indices of the dice to keep and NOT Rolled
	vector<int> keptDices;
	// stores the matching categories based on the dice 
	vector<int> availableCategory;
	// Note: The above vector doesn't check if that category is already filled in the scorecard

	// to retrive the combinations available on the dice
	Combinations board;
	 
};
