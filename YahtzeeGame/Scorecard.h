#pragma once

#include "stdafx.h"
//#include "Round.h"

struct card {
	string name;
	int score;
	int player_id;
	int round_no;
};


class Scorecard
{

public:
	Scorecard();
	~Scorecard();

	int getCategoryScore(int category);
	int getTotal(int player_id);

	bool isScorecardFull();
	bool isCategoryFill(int category_id);
	// returns the player with the lowest score
	int playerWithLowestScore(); 

	void setScore(int category_id, int score, int player_id);

	void displayScorecard();
	// to record the scores for each category
	static vector<card> scoreCard; 

	

private:

	// to record the names of the categories
	vector<string> categories; 
	// to record the scores for each category
	vector<int> scores;

};



