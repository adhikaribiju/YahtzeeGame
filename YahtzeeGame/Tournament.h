#pragma once
#include "stdafx.h"
#include "Round.h"
#include "Scorecard.h"
#include "Serialization.h"

class Tournament {
public:
	Tournament();
	~Tournament();

	void startTournament(); // starts the tournament
	void loadTournament(); // loads a tournament from a file

	void displayWinner(int player1, int player2);


private:
	const int HUMAN = 1; // to represent the human player || This is the id for the human player
	const int COMPUTER = 2; // to represent the computer player || This is the id for the computer player

	int humanRoll; // to store the human player's roll during the first round
	int computerRoll; // to store the human player's roll during the first round
	Serialization serialize; // to save and load the game
	
};