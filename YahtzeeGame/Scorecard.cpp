#include "Scorecard.h"


//int Round::numOfRounds;
//vector<card> Scorecard::scoreCard;

vector<card>Scorecard::scoreCard = {
	{"Aces", 0, 0},
	{"Twos", 0, 0},
	{"Threes", 0, 0},
	{"Fours", 0, 0},
	{"Fives", 0, 0},
	{"Sixes", 0, 0},
	{"Three of a Kind", 0, 0},
	{"Four of a Kind", 0, 0},
	{"Full House", 0, 0},
	{"Four Straight", 0, 0},
	{"Five Straight", 0, 0},
	{"Yahtzee", 0, 0}
};

Scorecard::Scorecard()
{
	// initialize the categories
	categories = { "Aces", "Twos", "Threes", "Fours",
		"Fives", "Sixes", "Three of a Kind", "Four of a Kind",
		"Full House", "Four Straight", "Five Straight",
		"Yahtzee" };

	// initialize the scores
	scores = {};

	// initialize the scorecard


}

Scorecard::~Scorecard()
{

}

void Scorecard::displayScorecard()
{

	cout << endl;
	cout << "        Scorecard        " << endl;
	cout << endl;
	cout << "----------------------------" << endl;
	cout << left << "C.N. " << setw(20) << "Category" << setw(10) << "Score" << endl;
	cout << "----------------------------" << endl;

	for (int i = 0; i < 12; i++) {
		// Left-align both columns and set field width
		cout << left << i + 1 << " : " << setw(20) << scoreCard[i].name << setw(10) << scoreCard[i].score << "  " << scoreCard[i].player_id << endl;
	}
}


// getter and setters for scores
void Scorecard::setScore(int category, int score, int player_id)
{
	//scores[category] = score;
	scoreCard[category].score = score;
	scoreCard[category].player_id = player_id;
}

int Scorecard::getCategoryScore(int category)
{
	return scoreCard[category].score;
}


int Scorecard::getTotal(int player_id)
{
	int sum = 0;

	for (int i = 0; i < 12; i++) {
		if (player_id == scoreCard[i].player_id) sum += scoreCard[i].score;
	}

	return sum;
}

bool Scorecard::isScorecardFull()
{
	for (int i = 0; i < 12; i++) {
		if (scoreCard[i].score == 0) {
			return false;
		}
	}
	return true;
}


int Scorecard::playerWithLowestScore()
{
	// calculate player 1's score
	//calculate player 2's score

	int player1_score = getTotal(1);
	int player2_score = getTotal(2);

	if (player1_score < player2_score) {
		return 1;
	}
	else {
		return 2;
	}

}


bool Scorecard::isCategoryFill(int category)
{
	if (scoreCard[category].player_id == 0) {
		return false;
	}
	else {
		return true;
	}
}

