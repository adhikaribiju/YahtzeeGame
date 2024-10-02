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

	// to play a turn for human player
	void playTurn() override;

	// to score the category
	void scoreCategory(Combinations board);


	// Below are the functions that are used to help the user
	void findScorebyCategory();
	void viewHelp(vector<int>& dice);
	// provides help in choosing the max score
	bool helpStrategy(vector<int>& dice);
	// to check if the lower section is filled
	bool lowerSectionFilled();
	// to display the highest possible score
	void displayHighestScore();
	// to see if Yahtzee is possible
	void tryYahtzee();
	// to check if a sequential is possible
	bool isSequentialAvailable();

private:
	// to store the user's input
	string user_dice;

	//to store the user's dice that they wish to keep
	int dice_to_reroll;
	// used for testing to specify the exact number in each dice
	int dice_num;
	// to store the category choice of the user
	int category_choice;
	// to record the index of the dice to Roll/keep
	int diceLocation;


	// to check if the help has been shown
	bool helpShown;
	// to check if the dice has been kept || Used for providing help
	bool keepFlag;


	// this vector holds the dice that are kept
	vector<int> keepDice;
	// to store the available scores for the categories
	vector<pair<int, int>> availableScores;
	// retrive the combinations available on the dice
	Combinations help_board;

};