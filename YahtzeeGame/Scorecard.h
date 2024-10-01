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
	int playerWithLowestScore(); // returns the player with the lowest score

	void setScore(int category_id, int score, int player_id);

	void displayScorecard();

	static vector<card> scoreCard; // to record the scores for each category

	

private:

	vector<string> categories; // to record the names of the categories
	vector<int> scores; // to record the scores for each category

};



