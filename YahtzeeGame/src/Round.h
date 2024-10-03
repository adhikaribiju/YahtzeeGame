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

	// returns true if user decides to save game
	bool isSaveGame();
	// returns the number of rounds played
	const int getRoundNo();
	// returns the index of the dice to keep
	int diceIndex(int dice_to_keep);

	// starts a round consisting of two turns
	void playRound(int player_id);
	// resumes a round consisting of two turns
	void resumeRound(int player_id);
	// displays the dice values
	void displayDice();

	// to track the number of rounds played;
	static int numOfRounds;

private:
	// to record the number of dice
	const int NUM_OF_DICE = 5;

	// to store the player id
	int player_id;
	// to store the player's choice of dice roll
	char player_choice;
	//  to record the number of rolls taken in a turn
	int num_rolls;

	// to record the dice values
	vector<int> dice;
};