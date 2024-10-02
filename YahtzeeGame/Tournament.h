#pragma once
#include "stdafx.h"
#include "Round.h"
#include "Scorecard.h"
#include "Serialization.h"

class Tournament {
public:
	Tournament();
	~Tournament();

	// starts the tournament
	void startTournament();
	// loads a tournament from a file
	void loadTournament(); 

	void displayWinner(int player1, int player2);


private:
	// to represent the human player || This is the id for the human player
	const int HUMAN = 1;
	// to represent the computer player || This is the id for the computer player
	const int COMPUTER = 2;


	// to store the human player's roll during the first round
	int humanRoll;
	// to store the human player's roll during the first round
	int computerRoll;
	// to save and load the game
	Serialization serialize;
};