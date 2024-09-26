#pragma once

#include "stdafx.h"

struct card {
	string name;
	int score;
	int player_id;
};


class Scorecard
{

public:
	Scorecard();
	~Scorecard();

	void displayScorecard();

	int getCategoryScore(int category);
	int getTotal(int player_id);

	bool isScorecardFull();
	bool isCategoryFill(int category_id);

	void setScore(int category_id, int score, int player_id);

	int playerWithLowestScore(); // returns the player with the lowest score

	//void setScore(int category, vector<int>& dice, int player_id);

	static vector<card> scoreCard;

	

private:

	vector<string> categories; // to record the names of the categories
	vector<int> scores; // to record the scores for each category

	int upperTotal;
	int lowerTotal;
	int grandTotal;

};



