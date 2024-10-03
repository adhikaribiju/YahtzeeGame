#include "Scorecard.h"


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

/* *********************************************************************
Function Name: displayScorecard
Purpose: To display the scorecard
Parameters:
	None
Return Value:
	None
Algorithm:
	1. Iterate through the scorecard
	2. Display the category number, category name, score, player, and round number
Reference: None
********************************************************************* */
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


/* *********************************************************************
Function Name: setScore
Purpose: To set the score for a category
Parameters:
	category, an integer
		the category number
	score, an integer
		the score for the category
	player_id, an integer
		the player id
Return Value:
	None
Algorithm:
	1. Set the score for the category in the scorecard vector
Reference: None
********************************************************************* */
void Scorecard::setScore(int category, int score, int player_id)
{
	
	scoreCard[category].score = score;
	scoreCard[category].player_id = player_id;
}

/* *********************************************************************
Function Name: getCategoryScore
Purpose: To get the score for a category
Parameters:
	category, an integer
		the category number
Return Value:
	the score for the category
Algorithm:
	1. Get the score for the given category
	2. Return the score
Reference: None
********************************************************************* */
int Scorecard::getCategoryScore(int category)
{
	return scoreCard[category].score;
}

/* *********************************************************************
Function Name: getTotal
Purpose: To get the total score for a player
Parameters:
	player_id, an integer
		the player id
Return Value:
	the total score for the player
Algorithm:
	1. Iterate through the scorecard vector
	2. Add the score for the player given the player id in the scorecard vector
	3. Return the total score
Reference: None
********************************************************************* */
int Scorecard::getTotal(int player_id)
{
	int sum = 0;

	for (int i = 0; i < 12; i++) {
		if (player_id == scoreCard[i].player_id) sum += scoreCard[i].score;
	}

	return sum;
}

/* *********************************************************************
Function Name: isCategoryFill
Purpose: To check if a category is filled
Parameters:
	category, an integer
		the category number
Return Value:
	true if the category is filled, false otherwise
Algorithm:
	1. Check if the score for the category is 0
	2. If the score is 0, return false
	3. If the score is not 0, return true
Reference: None
********************************************************************* */
bool Scorecard::isScorecardFull()
{
	for (int i = 0; i < 12; i++) {
		if (scoreCard[i].score == 0) {
			return false;
		}
	}
	return true;
}

/* *********************************************************************
Function Name: playerWithLowestScore
Purpose: To get the player with the lowest score
Parameters:
	None
Return Value:
	int, the player with the lowest score
Algorithm:
	1. Calculate the total score for player 1
	2. Calculate the total score for player 2
	3. Compare the total scores
	4. Return the player with the lowest score
Reference: None
********************************************************************* */
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

/* *********************************************************************
Function Name: isCategoryFill
Purpose: To check if a category is filled
Parameters:
	category, an integer
		the category number
Return Value:
	true if the category is filled, false otherwise
Algorithm:
	1. Check if the score for the category is 0
	2. If the score is 0, return false
	3. If the score is not 0, return true
Reference: None
********************************************************************* */
bool Scorecard::isCategoryFill(int category)
{
	if (scoreCard[category].score == 0) { // changed from player_id to score
		return false;
	}
	else {
		return true;
	}
}

