#pragma once
#include "stdafx.h"
#include "Scorecard.h"
#include "Combinations.h"
#include "Human.h"
#include "Computer.h"
#include "Serialization.h"


class Round {
public:

	Round();
	~Round();

	bool isSaveGame(); // returns true if user decides to save game
	const int getRoundNo(); // returns the number of rounds played
	int diceIndex(int dice_to_keep); // returns the index of the dice to keep

	void playRound(int player_id); // starts a round consisting of two turns
	void displayDice(); // displays the dice values

	static int numOfRounds; // to track the number of rounds played;

private:
	
	const int NUM_OF_DICE = 5; // to record the number of dice

	int player_id;
	char player_choice; // to record the player's choice of dice roll
	int num_rolls; // to record the number of rolls taken in a turn

	vector<int> dice; // to record the dice values
	

};