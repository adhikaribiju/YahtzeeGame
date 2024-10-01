#pragma once

#include "stdafx.h"
#include "Scorecard.h"
#include "Player.h"

class Human : public Player {
public:
	Human();
	~Human();

	void playTurn();
	void reRoll();
	void customFill();
	void scoreCategory(Combinations board);


private:
	string user_dice; // to store the user's input
	int dice_to_reroll; //to store the user's dice that they wish to keep
	int dice_num; // used for testing to specify the exact number in each dice
	int category_choice; 
	vector<int> keepDice; // this vector holds the dice that are kept
	int diceLocation; // to record the index of the dice to Roll/keep
};