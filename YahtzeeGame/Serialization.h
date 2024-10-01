#pragma once
#include "stdafx.h"
#include "Scorecard.h"
#include "Round.h"

class Serialization {

public:
	Serialization();
	~Serialization();


	int getCurrentRound();

	// to check if the file exists 
	bool validateFile(const string& fileName);
	// to process the file
	bool readFile(const string& fileName);

	bool saveGame();
	void loadGame();
	void displayLoadedScorecard();

	Scorecard scorecard;

private:
	int currentRound;
};
