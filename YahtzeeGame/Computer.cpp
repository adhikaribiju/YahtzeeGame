#include "Computer.h"

Computer::Computer() {
	num_rolls = 1;
	reroll = false;
}

Computer::~Computer() {

}

void Computer::playTurn() {
	cout << "Computer is playing....." << endl;

	playRoll(); // Roll the 5 dice randomly OR manually  // THIS NEEDS OVERRIDING..
	displayDice(); // display the dice values

	board.updateDice(dice); // retrive the combinations

	board.displayScorecard(); // display the available combinations

	availableCategory = board.availableCombinations();
	board.displayAvailableCombinations();

	findCategoryScore(); // fill the scoresAvailable vector of pair of ints

	while (num_rolls <= 3 && !reroll)
	{
		reroll = computerDecide();
		num_rolls++;
	}


	


	//{Computer gets 2 more rolls to come up with the category to score}
	//{After 2nd roll, the computer can keep certain dice and reroll the rest}
	//{After 3rd roll, the computer can keep certain dice and reroll the ones that were not kept}
	//{After 3rd roll, the computer must choose a category to score if available}
	

	// Check the max score available to score // if more than or equal to 25 score it


}

void Computer::findCategoryScore() {


	if (availableCategory.size() != 0) {

		for (int i = 1; i <= 6; i++)
		{
			int score = board.calculateUpperSectionScore(i);
			if (score != 0) scoresAvailable.push_back({ i-1, score });
		}

		int totalDice = board.sumAllDice();

		if (board.hasThreeOfAKind() && !board.isCategoryFill(6)) {
			scoresAvailable.push_back({ 6, totalDice });
		}

		// Check for Four of a Kind
		if (board.hasFourOfAKind() && !board.isCategoryFill(7)) {
			scoresAvailable.push_back({ 7, totalDice });
		}
			// Check for Full House
			if (board.hasFullHouse() && !board.isCategoryFill(8)) {
				scoresAvailable.push_back({ 8, 25 });
			}

			// Check for Small Straight
			if (board.hasFourStraight() && !board.isCategoryFill(9)) {
				scoresAvailable.push_back({ 9, 30 });
			}

			// Check for Large Straight
			if (board.hasFiveStraight() && !board.isCategoryFill(10)) {
				scoresAvailable.push_back({ 10, 40 });
			}

			// Check for Yahtzee
			if (board.hasYahtzee() && !board.isCategoryFill(11)) {
				scoresAvailable.push_back({ 11, 50 });
			}
		}
	}



bool Computer::computerDecide() {


	for (int i = scoresAvailable.size() - 1; i >= 0; i--) {
		if (scoresAvailable[i].second >= 20 && !board.isCategoryFill(scoresAvailable[i].first + 1)) {
			board.setScore(scoresAvailable[i].first, 2);
			return true; // category selected
		}
	}
	// If there is no score>=20

	// is roll left?
	if (num_rolls <= 3) {

		// Check if Lower Section is available to score
			// retrun false if lower section completely not filled
		if (lowerSectionFilled()) {

			// This means upper section is available to score
			// Do we have any category in dice right now?
			// If yes, score the highest available
			// If not, roll all dice
			if (availableCategory.size() == 0)
			{
				scoreHighestAvailable();
				return true; // category selected
			}
			else {
				playRoll();
				return true; // ALL DICE RE-ROLLED 
			}
		}
		else {
			// At this point, check if score availble is >=10
			// If Yes, Score it
			for (int i = scoresAvailable.size() - 1; i >= 0; i--) {
				if (scoresAvailable[i].second >= 10 && !board.isCategoryFill(scoresAvailable[i].first + 1)) {
					board.setScore(scoresAvailable[i].first, 2);
					return true; // category selected
				}
			}
			// If Not, check 3 or 4 of kind available

			for (int i = scoresAvailable.size() - 1; i >= 0; i--) {
				// if 3/4 of a kind available, score it NO MATTER HOW SMALL THE SCORE
				if (scoresAvailable[i].first + 1 == 7 || scoresAvailable[i].first + 1 == 8) {
					board.setScore(scoresAvailable[i].first, 2);
					return true; // category selected
				}
			}


			// From this point, we will try to keep certain dice faces and reroll the rest
			// Keep in mind that, you can only reroll the dice that hasn't be kept before
			// In the case, computer chooses to reroll certain dice that were already kept, it will trigger roll conflict
			// Roll conflict will reroll all the other dices.





		}

	}
	else { // No rolls left so score whatever available
		scoreHighestAvailable();
		return true; // category selected
	}

	return false;
}


// to check if lower section is left to score

// retrun false if lower section completely not filled
// return true if lower section is completely filled
bool Computer::lowerSectionFilled() {
	for (int i = 6; i < 12; i++)
	{
		if (board.scoreCard[i].player_id == 0) return false;
	}
	return true;
}

void Computer::scoreHighestAvailable()
{
	for (int i = scoresAvailable.size() - 1; i >= 0; i--) {
		if (!board.isCategoryFill(scoresAvailable[i].first + 1)) {
			board.setScore(scoresAvailable[i].first, 2);
		}
	}
}