#include "Scorecard.h"


//int Round::numOfRounds;
//vector<card> Scorecard::scoreCard;

vector<card>Scorecard::scoreCard = {
	{"Aces", 0, 0, 0},
	{"Twos", 0, 0, 0},
	{"Threes", 0, 0, 0},
	{"Fours", 0, 0, 0},
	{"Fives", 0, 0, 0},
	{"Sixes", 0, 0, 0},
	{"Three of a Kind", 0, 0, 0},
	{"Four of a Kind", 0, 0, 0},
	{"Full House", 0, 0, 0},
	{"Four Straight", 0, 0, 0},
	{"Five Straight", 0, 0, 0},
	{"Yahtzee", 0, 0, 0}
};

Scorecard::Scorecard()
{
	// initialize the categories
	categories = { "Aces", "Twos", "Threes", "Fours",
		"Fives", "Sixes", "Three of a Kind", "Four of a Kind",
		"Full House", "Four Straight", "Five Straight",
		"Yahtzee" };

	
	scores = {}; // initialize the scores

}

Scorecard::~Scorecard()
{

}

void Scorecard::displayScorecard()
{
	
	cout << endl;
	cout << "\t\t\tScorecard" << endl;
	cout << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << left << setw(17) << "Category No." << setw(25) << "Category" << setw(10) << "Score" << setw(10) << "Player" << setw(10) << "Round" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	string player = " ";
	for (int i = 0; i < 12; i++) {

		if (scoreCard[i].player_id == 1) player = "You";
		else if (scoreCard[i].player_id == 2) player = "Computer";
		else player = "X";

		// Left-align columns and set field width for neat alignment
		cout << left << setw(17) << i + 1 << setw(25) << scoreCard[i].name << setw(10) << scoreCard[i].score << setw(10) << player << setw(10) << scoreCard[i].round_no << endl;
	}

}


// setters for scores
void Scorecard::setScore(int category, int score, int player_id)
{
	
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
	if (scoreCard[category].score == 0) { // changed from player_id to score
		return false;
	}
	else {
		return true;
	}
}

