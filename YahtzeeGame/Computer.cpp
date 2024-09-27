#include "Computer.h"

Computer::Computer() {
	num_rolls = 1;
}

Computer::~Computer() {

}

void Computer::playComputer() {
	cout << "Computer is playing....." << endl;

	playRoll(); // Roll the 5 dice randomly OR manually  // THIS NEEDS OVERRIDING..
	displayDice(); // display the dice values

	Combinations board(dice); // retrive the combinations

	board.displayScorecard(); // display the available combinations
	board.availableCombinations(); // display the available combinations



	//{Computer gets 2 more rolls to come up with the category to score}
	//{After 2nd roll, the computer can keep certain dice and reroll the rest}
	//{After 3rd roll, the computer can keep certain dice and reroll the ones that were not kept}
	//{After 3rd roll, the computer must choose a category to score if available}



	// At this point dice roll has either been completed or the user has chosen not to roll again
	// Now the user has to choose a category to score IF AVAILABLE
	//scoreCategory(board);

}

