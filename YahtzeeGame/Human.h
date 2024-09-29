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
	int dice_to_keep; //to store the user's dice that they wish to keep
	int dice_num; // used for testing to specify the exact number in each dice
	int category_choice; 
};