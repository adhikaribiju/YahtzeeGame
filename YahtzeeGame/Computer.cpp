#include "Computer.h"
using namespace std;

Computer::Computer() {
	num_rolls = 1;
	reroll = false;
	keepError = false;
	isScoreSet = false;
	
}

Computer::~Computer() {

}

void Computer::playTurn() {
	cout << "\nComputer is playing....." << endl;

	isScoreSet = false;

	playRoll(); // Roll the 5 dice randomly OR manually  // THIS NEEDS OVERRIDING..
	displayDice(); // display the dice values

	board.updateDice(dice); // retrive the combinations

	board.displayScorecard(); // display the available combinations

	availableCategory = board.availableCombinations();
	board.displayAvailableCombinations();

	keptDices.clear();

	while (num_rolls <= 3 && !reroll && !keepError)
	{
		if (num_rolls >= 2) { displayDice(); } // display the dice values
		findCategoryScore(); // fill the scoresAvailable vector of pair of ints
		reroll = computerDecide();
		num_rolls++;
	}

	if (keepError && !isScoreSet) {
		//score the max available if any
		int highestIndex = -1;
		int highestScore = -1;
		findCategoryScore(); // Since the dice was re-rolled
		// Loop through the scoresAvailable vector to find the category with the highest score
		for (int i = 0; i < scoresAvailable.size(); i++) {
			if (!board.isCategoryFill(scoresAvailable[i].first)) {
				if (scoresAvailable[i].second > highestScore) {
					highestScore = scoresAvailable[i].second;
					highestIndex = i;
				}
			}
		}

		// If a valid index was found, set the score for that category
		if (highestIndex != -1) {
			board.setScore(scoresAvailable[highestIndex].first, 2);
			isScoreSet = true;
		}
	}

	if (!isScoreSet) cout << "Nothing to score, so skipping turn" << endl;


	cout << "\n\nComputer's Turn Ended!" << endl;


	//{Computer gets 2 more rolls to come up with the category to score}
	//{After 2nd roll, the computer can keep certain dice and reroll the rest}
	//{After 3rd roll, the computer can keep certain dice and reroll the ones that were not kept}
	//{After 3rd roll, the computer must choose a category to score if available}
	

	// Check the max score available to score // if more than or equal to 25 score it


}

void Computer::findCategoryScore() {

	scoresAvailable.clear();
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
	isScoreSet = false;

	for (int i = scoresAvailable.size() - 1; i >= 0; i--) {
		if (scoresAvailable[i].second >= 20 && !board.isCategoryFill(scoresAvailable[i].first)) {
			board.setScore(scoresAvailable[i].first, 2);
			isScoreSet = true;
			return true; // category selected
		}
	}
	// If there is no score>=20
	if (!isScoreSet) {
		// is roll left?
		if (num_rolls <= 3) {

			// Check if Lower Section is available to score
				// retrun false if lower section completely not filled
			if (lowerSectionFilled()) {

				// This means upper section is available to score
				// Do we have any category in dice right now?
				// If yes, score the highest available
				// If not, roll all dice
				if (!availableCategory.empty())
				{
					scoreHighestAvailable();
					return true; // category selected
				}
				else {
					playRoll();
					board.updateDice(dice);
					board.displayAvailableCombinations(); // display the available combinations
					return true; // ALL DICE RE-ROLLED 
				}
			}
			else {
				// At this point, check if score availble is >=10
				// If Yes, Score it
				for (int i = scoresAvailable.size() - 1; i >= 0; i--) {
					if (scoresAvailable[i].second >= 10 && !board.isCategoryFill(scoresAvailable[i].first)) {
						board.setScore(scoresAvailable[i].first, 2);
						isScoreSet = true;
						return true; // category selected
					}
				}
				// If Not, check 3 or 4 of kind available
				if (!isScoreSet) {
					for (int i = scoresAvailable.size() - 1; i >= 0; i--) {
						// if 3/4 of a kind available, score it NO MATTER HOW SMALL THE SCORE
						if (scoresAvailable[i].first + 1 == 7 || scoresAvailable[i].first + 1 == 8) {
							board.setScore(scoresAvailable[i].first, 2);
							isScoreSet = true;
							return true; // category selected
						}
					}
				}


				// From this point, we will try to keep certain dice faces and reroll the rest
				// Keep in mind that, you can only reroll the dice that hasn't be kept before
				// In the case, computer chooses to reroll certain dice that were already kept, it will trigger roll conflict
				// Roll conflict will reroll all the other dices.


				// Check if dice has 3 sequential numbers
				// If yes, check if five/four straight are available to score
				//			If yes, keep the 3 sequential numbers and reroll the rest
				//			If no,	CHECK FOR Non-SEQUENTIAL NUMBERS




				if (isSequentialAvailable()) {
					board.updateDice(dice);
					board.displayAvailableCombinations(); // display the available combinations
					return false; // dice was kept or rerolled
				}
				else {// Check for Non-SEQUENTIAL NUMBERS

					tryYahtzeeOrFullHouse();
					return false; // dice was kept or rerolled
				}


			}

		}
		else { // No rolls left so score whatever available
			scoreHighestAvailable();
			return true; // category selected
		}
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


bool Computer::isSequentialAvailable()
{
	vector<int> count(7, 0);  // Initialize count vector with 7 elements, all set to 0
	vector<int> sequenceIndices; // To store indices of dice that match the sequence

	int numOfOnes = 0;
	bool sequenceFound = false;
	bool diceRoll = false;

	// Record the count of numbers on the dice
	for (int die : dice) {
		if (die >= 1 && die <= 6) {
			count[die]++;
		}
	}

	// Check for the specific consecutive sequences {1, 2, 3} or {2, 3, 4}
	if (count[1] >= 1 && count[2] >= 1 && count[3] >= 1) {
		sequenceFound = true;  // Sequence {1, 2, 3} found
	}
	else if (count[2] >= 1 && count[3] >= 1 && count[4] >= 1) {
		sequenceFound = true;  // Sequence {2, 3, 4} found
	}

	if (sequenceFound && (!board.isCategoryFill(9) || !board.isCategoryFill(10))) {
		// Add dice involved in the sequence to keptDices
		for (int i = 0; i < dice.size(); ++i) {
			int value = dice[i];
			if ((value == 1 || value == 2 || value == 3) ||  // For sequence {1, 2, 3}
				(value == 2 || value == 3 || value == 4)) {  // For sequence {2, 3, 4}
				// If the index is already in keptDices, set keepError to true
				if (find(keptDices.begin(), keptDices.end(), i) != keptDices.end()) {
					keepError = true;
				}
				else {
					// Otherwise, add the index to keptDices
					keptDices.push_back(i);
				}
			}
		}

		// Re-roll dice that are not part of the sequence
		srand((unsigned)time(0));  // Initialize random seed
		std::cout << "Computer decided to roll: "; // getting cout is ambigious error so used std::cout
		for (int i = 0; i < dice.size(); ++i) {
			int value = dice[i];
			// Re-roll only dice that are not part of the sequence
			if ((value != 1 && value != 2 && value != 3) &&  // Not in {1, 2, 3}
				(value != 2 && value != 3 && value != 4)) {  // Not in {2, 3, 4}
				std::cout << value << " ";
				dice[i] = ((rand() % 6) + 1);  // Roll a new random dice value
				diceRoll = true;
			}
		}
		std::cout << endl;

		if (!diceRoll) {
			if (!keepError) {
				cout << " all dices." << endl;
				playRoll();
				board.updateDice(dice);
			}
		}
		return true;  // Sequence was found and dice were kept/rolled
	}

	return false;  // No valid sequence found

}


void Computer::tryYahtzeeOrFullHouse() {
	bool threeOfAKind = false;
	bool twoOfAKind = false;
	int targetValueThreeOfAKind = -1;  // Target value for "three of a kind"
	int targetValueTwoOfAKind = -1;    // Target value for "two of a kind"


	vector<int> count;

	int numOfones = 0;
	// Initializing the count vector
	for (int i = 0; i < 7; i++)
	{
		count.push_back(0);
	}

	// Recording the count of numbers on the dice
	for (int die : dice) {
		if (die >= 1 && die <= 6) {
			count[die]++;
		}
	}

	// Step 1: Check if any dice number has count > 3 (three of a kind)
	for (int i = 1; i < count.size(); ++i) {
		if (count[i] >= 3) {
			threeOfAKind = true;
			targetValueThreeOfAKind = i;
		}
	}

	// Step 2: If no three of a kind, check for two of a kind (count > 2)
	if (!threeOfAKind) {
		for (int i = 1; i < count.size(); ++i) {
			if (count[i] >= 2) {
				twoOfAKind = true;
				targetValueTwoOfAKind = i;
			}
		}
	}

	// Step 3: Prepare to log the dice values being rolled
	cout << "Computer decided to roll: ";
	bool anyRolled = false;  // A flag to check if any dice is being rolled

	// Step 4: Roll the dice based on the conditions
	srand(time(0));  // Seed for random number generation
	for (int i = 0; i < dice.size(); ++i) {
		if (threeOfAKind) {
			// Roll all dice except those that have the value matching the three of a kind
			if (dice[i] != targetValueThreeOfAKind && (find(keptDices.begin(), keptDices.end(), i) == keptDices.end())) {
				cout << dice[i] << " ";  // Log the value being rolled
				dice[i] = ((rand() % 6) + 1);  // Roll the dice
				anyRolled = true;
			}
			else if (find(keptDices.begin(), keptDices.end(), i) == keptDices.end()) {
				// If dice is not being rolled, add it to keptDices
				keptDices.push_back(i);
			}
			else {
				// If the dice is already in keptDices, set keptError to true
				keepError = true;
			}
		}
		else if (twoOfAKind) {
			// Roll all dice except those that have the value matching the two of a kind
			if (dice[i] != targetValueTwoOfAKind && (find(keptDices.begin(), keptDices.end(), i) == keptDices.end())) {
				cout << dice[i] << " ";  // Log the value being rolled
				dice[i] = ((rand() % 6) + 1);  // Roll the dice
				anyRolled = true;
			}
			else if (find(keptDices.begin(), keptDices.end(), i) == keptDices.end()) {
				// If dice is not being rolled, add it to keptDices
				keptDices.push_back(i);
			}
			else {
				// If the dice is already in keptDices, set keptError to true
				keepError = true;
			}
		}
		else {
			// If no "three of a kind" or "two of a kind" found, roll all dice
			cout << dice[i] << " ";  // Log the value being rolled
			dice[i] = ((rand() % 6) + 1);  // Roll the dice
			anyRolled = true;
		}
	}
	cout << endl;

	if (anyRolled) {
		board.updateDice(dice);
		board.displayAvailableCombinations(); // display the available combinations
		cout << endl; // new line
	}

}