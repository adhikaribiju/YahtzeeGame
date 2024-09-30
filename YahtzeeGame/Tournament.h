#pragma once
#include "stdafx.h"
#include "Round.h"
#include "Scorecard.h"
#include "Serialization.h"

class Tournament {
public:
	Tournament();
	~Tournament();

	// functions here
	void startTournament();
	void loadTournament();
	void endTournament();

	void displayWinner(int p1, int p2);


private:

	int humanRoll;
	int computerRoll;

	// variables here

	Serialization serialize;




};