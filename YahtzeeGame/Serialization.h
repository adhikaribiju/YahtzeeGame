#pragma once
#include "stdafx.h"
#include "Scorecard.h"
#include "Round.h"

class Serialization {

public:
	Serialization();
	~Serialization();

	bool saveGame();
	void loadGame();

	// to check if the file exists 
	bool validateFile(const string& fileName);

	// to process the file
	bool readFile(const string& fileName);

	void displayLoadedScorecard();
	int getCurrentRound();

	Scorecard scorecard;

private:
	int currentRound;
};
