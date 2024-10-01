#pragma once

#include "stdafx.h"
#include "Scorecard.h"
#include "Player.h"

class Human : public Player {
public:
	Human();
	~Human();

	void reRoll();
	void customFill();

	void playTurn();
	void scoreCategory(Combinations board);


	// Below are the functions that are used to help the user
	void findScorebyCategory();
	void viewHelp(vector<int>& dice);
	bool helpStrategy(vector<int>& dice); // provides help in choosing the max score
	bool lowerSectionFilled(); // to check if the lower section is filled
	void displayHighestScore(); // to display the highest possible score
	void tryYahtzee(); // to see if Yahtzee is possible
	bool isSequentialAvailable(); // to check if a sequential is possible

private:
	string user_dice; // to store the user's input

	int dice_to_reroll; //to store the user's dice that they wish to keep
	int dice_num; // used for testing to specify the exact number in each dice
	int category_choice; 
	int diceLocation; // to record the index of the dice to Roll/keep

	bool helpShown; // to check if the help has been shown
	bool keepFlag; // to check if the dice has been kept || Used for providing help

	vector<int> keepDice; // this vector holds the dice that are kept
	vector<pair<int, int>> availableScores; // to store the available scores for the categories
	Combinations help_board; // retrive the combinations

};