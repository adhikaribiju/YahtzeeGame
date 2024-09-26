#pragma once
#include "stdafx.h"
#include "Scorecard.h"
#include "Combinations.h"


class Round {
public:
	//Round(Scorecard scorecard);
	Round();
//	Round(Scorecard scorecard, int player_id);
	~Round();

	void playRound(int player_id);
	void playTurn(int player_id);
	void playRoll();
	

	int diceIndex(int dice_to_keep);
	void displayDice();

//	Scorecard scorecard; // to view/change the scorecard


private:
	int player_id;
	char player_choice; // to record the player's choice of dice roll
	int max_rolls = 3; // to record the maximum number of rolls allowed in a turn
	int num_rolls = 1; // to record the number of rolls taken in a turn

	vector<int> dice; // to record the dice values
	int num_of_dice = 5; // to record the number of dice

	int numOfRounds; // to track the number of rounds played;

	
};