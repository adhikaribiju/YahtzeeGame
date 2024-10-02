#include "Combinations.h"
#include "Round.h"

Combinations::Combinations() {
	// Initialize counts to zero
	for (int i = 1; i <= MAX_DICE_VALUE; ++i) {
		counts[i] = 0;
	}
}
Combinations::Combinations(vector<int>& dice_values) {
    // Counting frequencies of each die face

    for (int i = 0; i < DICE_COUNT; i++) {
        dice.push_back(dice_values[i]);
    }

    // Initialize counts to zero
    for (int i = 1; i <= MAX_DICE_VALUE; ++i) {
        counts[i] = 0;
    }
}


/* *********************************************************************
Function Name: hasThreeOfAKind
Purpose: To check if the dice combination has three of a kind
Parameters:
    None
Return Value:
    - 'true' if the dice combination has three of a kind, 'false' otherwise
Algorithm:
    1. Iterate through the counts array.
    2. If the count of any die face is greater than or equal to 3, return 'true'.
    3. If no die face has a count greater than or equal to 3, return 'false'.
Reference: none
********************************************************************* */
bool Combinations::hasThreeOfAKind() const {
    for (int i = 1; i <= MAX_DICE_VALUE; ++i) {
        if (counts[i] >= 3) {
            return true;
        }
    }
    return false;
}

/* *********************************************************************
Function Name: hasFourOfAKind
Purpose: To check if the dice combination has four of a kind
Parameters:
    None
Return Value:
    - 'true' if the dice combination has four of a kind, 'false' otherwise
Algorithm:
    1. Iterate through the counts array.
    2. If the count of any die face is greater than or equal to 4, return 'true'.
    3. If no die face has a count greater than or equal to 4, return 'false'.
Reference: none
********************************************************************* */
bool Combinations::hasFourOfAKind() const {
    for (int i = 1; i <= MAX_DICE_VALUE; ++i) {
        if (counts[i] >= 4) {
            return true;
        }
    }
    return false;
}

/* *********************************************************************
Function Name: hasYahtzee
Purpose: To check if the dice combination has a Yahtzee
Parameters:
    None
Return Value:
    - 'true' if the dice combination has a Yahtzee, 'false' otherwise
Algorithm:
    1. Iterate through the counts array.
    2. If the count of any die face is equal to 5, return true.
    3. If no die face has a count equal to 5, return false.
Reference: none
********************************************************************* */
 bool Combinations::hasYahtzee() const {
    for (int i = 1; i <= MAX_DICE_VALUE; ++i) {
        if (counts[i] == 5) {
            return true;
        }
    }
    return false;
}

 /* *********************************************************************
Function Name: hasFullHouse
Purpose: To check if the dice combination has a Full House
Parameters:
    None
Return Value:
    - 'true' if the dice combination has a Full House, 'false' otherwise
Algorithm:
    1. Initialize two boolean variables, hasThree and hasTwo, to false.
    2. Iterate through the counts array.
    3. If the count of any die face is equal to 3, set hasThree to true.
    4. If the count of any die face is equal to 2, set hasTwo to true.
    5. If the dice combination has a Yahtzee, return true.
    6. Return true if hasThree and hasTwo are both true, false otherwise.
Reference: none
********************************************************************* */
 bool Combinations::hasFullHouse() const {
    bool hasThree = false;
    bool hasTwo = false;
    for (int i = 1; i <= MAX_DICE_VALUE; ++i) {
        if (counts[i] == 3) {
            hasThree = true;
        }
        else if (counts[i] == 2) {
            hasTwo = true;
        }
    }
    // Special case: Yahtzee counts as a Full House
    if (hasYahtzee()) {
        return true;
    }
    return hasThree && hasTwo;
}

 /* *********************************************************************
Function Name: hasFourStraight
Purpose: To check if the dice combination has a Four Straight
Parameters:
    None
Return Value:
    - 'true' if the dice combination has a Four Straight, 'false' otherwise
Algorithm:
    1. Check for the following sequences: 1-2-3-4, 2-3-4-5, 3-4-5-6.
    2. If any of the sequences is present, return 'true'.
    3. If none of the sequences is present, return 'false'.
Reference: none
********************************************************************* */
 bool Combinations::hasFourStraight() const {
    // Possible sequences: 1-2-3-4, 2-3-4-5, 3-4-5-6

    // Check for sequence 1-2-3-4
    if (counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1) {
        return true;
    }
    // Check for sequence 2-3-4-5
    if (counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1) {
        return true;
    }
    // Check for sequence 3-4-5-6
    if (counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1 && counts[6] >= 1) {
        return true;
    }
    return false;
}

 /* *********************************************************************
Function Name: hasFiveStraight
Purpose: To check if the dice combination has a Five Straight
Parameters:
    None
Return Value:
    - 'true' if the dice combination has a Five Straight, 'false' otherwise
Algorithm:
    1. Check for the following sequences: 1-2-3-4-5, 2-3-4-5-6.
    2. If any of the sequences is present, return true.
    3. If none of the sequences is present, return false.
Reference: none
********************************************************************* */
 bool Combinations::hasFiveStraight() const {
    // Possible sequences: 1-2-3-4-5, 2-3-4-5-6

    // Check for sequence 1-2-3-4-5
    if (counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1) {
        return true;
    }
    // Check for sequence 2-3-4-5-6
    if (counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1 && counts[6] >= 1) {
        return true;
    }
    return false;
}

 /* *********************************************************************
Function Name: calculateUpperSectionScore
Purpose: To calculate the score for a specific number in the upper section
Parameters:
    - number, an integer value representing the dice number of which the score is to be calculated
Return Value:
    int, the score for the specific number in the upper section
Algorithm:
    1. Initialize the sum to zero.
    2. Iterate through the dice vector.
    3. If the die face matches the number, add the die face value to the sum.
    4. Return the sum.
Reference: none
********************************************************************* */
int Combinations::calculateUpperSectionScore(int number) {
    int sum = 0;
    for (int die : dice) {
        if (die == number) {
            sum += die;
        }
    }
    return sum;
}

/* *********************************************************************
Function Name: sumAllDice
Purpose: To calculate the sum of all dice values
Parameters:
    None
Return Value:
    - The sum of all dice values
Algorithm:
    1. Initialize the total to zero.
    2. Iterate through the dice vector.
    3. Add the die face value to the total.
    4. Return the total.
Reference: none
********************************************************************* */
int Combinations::sumAllDice() {
    int total = 0;
    for (int die : dice) {
        total += die;
    }
    return total;
}

/* *********************************************************************
Function Name: availableCombinations
Purpose: To determine the available combinations to score based on the current dice values
Parameters:
    None
Return Value:
    - A vector of integers representing the available combinations to score
Algorithm:
    1. Clear the available combinations vector.
    2. Count the occurrences of each die face.
    3. Check for the following combinations and push to the vector if available:
        - Upper Section (Aces to Sixes)
        - Three of a Kind
        - Four of a Kind
        - Full House
        - Small Straight
        - Large Straight
        - Yahtzee
    4. Return the available combinations vector.
Reference: none
********************************************************************* */
vector<int> Combinations::availableCombinations() {
    available_combinations.clear();
    countDiceFace();
    // Upper Section (Aces to Sixes)
    for (int i = 1; i <= MAX_DICE_VALUE; ++i) {
        int score = calculateUpperSectionScore(i);
        if (score > 0) {
            available_combinations.push_back(i-1);
        }
    }

    if (hasThreeOfAKind()) {
        available_combinations.push_back(6);
    }

    // Check for Four of a Kind
    if (hasFourOfAKind()) {
        available_combinations.push_back(7);
    }

    // Check for Full House
    if (hasFullHouse()) {
        available_combinations.push_back(8);
    }

    // Check for Small Straight
    if (hasFourStraight()) {
        available_combinations.push_back(9);
    }

    // Check for Large Straight
    if (hasFiveStraight()) {
        available_combinations.push_back(10);
    }

    // Check for Yahtzee
    if (hasYahtzee()) {
        available_combinations.push_back(11);
    }
    return available_combinations;
}

/* *********************************************************************
Function Name: displayAvailableCombinations
Purpose: To display the available combinations to score based on the current dice values
Parameters:
	None
Return Value:
	None
Algorithm:
	1. Count the occurrences of each die face.
	2. Display the dice values.
	3. Display the potential categories to score (if any).
	4. Check for the following combinations and display if available:
		- Upper Section (Aces to Sixes)
		- Three of a Kind
		- Four of a Kind
		- Full House
		- Small Straight
		- Large Straight
		- Yahtzee
	Reference: none
********************************************************************* */
void Combinations::displayAvailableCombinations() {
    countDiceFace();
    cout << "Dice: ";
    for (int die : dice) {
        cout << die << " ";
    }
    cout << "\n\n";

    cout <<"Potential categories to score (if any): \n" << endl;
 

    // Upper Section (Aces to Sixes)
    for (int i = 1; i <= MAX_DICE_VALUE; ++i) {
        int score = calculateUpperSectionScore(i);
        if (score != 0 && !isCategoryFill(i-1)) {
            cout << "Category No. " << i << ": Score for " << scoreCard[i - 1].name << " : " << score << endl;
        }
    }
    

    int totalDice = sumAllDice();

    // Check for Three of a Kind
    if (hasThreeOfAKind() && !isCategoryFill(6)) {
        cout << "Category No. 7: Three of a Kind available! Score: " << totalDice << endl;
    }

    // Check for Four of a Kind
    if (hasFourOfAKind() && !isCategoryFill(7)) {
        cout << "Category No. 8: Four of a Kind available! Score: " << totalDice << endl;
    }

    // Check for Full House
    if (hasFullHouse() && !isCategoryFill(8)) {
        cout << "Category No. 9: Full House available! Score: 25" << endl;
    }

    // Check for Small Straight
    if (hasFourStraight() && !isCategoryFill(9)) {
        cout << "Category No. 10: Four Straight available! Score: 30" << endl;
    }

    // Check for Large Straight
    if (hasFiveStraight() && !isCategoryFill(10)) {
        cout << "Category No. 11: Five Straight available! Score: 40" << endl;
    }

    // Check for Yahtzee
    if (hasYahtzee()  && !isCategoryFill(11)) {
        cout << "Category No. 12: Yahtzee! Score: 50" << endl;
    }
}


/* *********************************************************************
Function Name: updateDice
Purpose: To update the dice values
Parameters:
	- dice_values, a vector of integers representing the dice values
Return Value:
	None
Algorithm:
	1. Clear the dice vector.
	2. Update the dice vector with the new dice values.
	3. Reset the count array.
Reference: none
********************************************************************* */
void Combinations::updateDice(vector<int>& dice_values) {
    dice.clear();
    for (int i = 0; i < DICE_COUNT; i++) {
        dice.push_back(dice_values[i]);
    }
    
    // reset the count array
	for (int i = 1; i <= MAX_DICE_VALUE; i++) {
		counts[i] = 0;
	}
}

/* *********************************************************************
Function Name: countDiceFace
Purpose: To count the occurrences of each die face
Parameters:
	None
Return Value:
	None
Algorithm:
	1. Initialize the counts array to zero.
	2. Iterate through the dice vector.
	3. If the die face is between 1 and 6, increment the count of the die face.
Reference: none
********************************************************************* */
void Combinations::countDiceFace() {
    // Count occurrences of each die face

    // initialize matra gareko ho
    for (int die : dice) {
        counts[die] = 0;
    }
    
    for (int die : dice) {
             if (die >= 1 && die <= 6) {
            counts[die]++;
        }
    }
}

/* *********************************************************************
Function Name: setScore
Purpose: To set the score for a specific category
Parameters:
	- category, an integer value representing the category to score
	- player_id, an integer value representing the player ID
Return Value:
	- 'true' if the score is set successfully, 'false' otherwise
Algorithm:
	1. Calculate the score based on the category.
	2. Set the score for the category.
	3. Display the score and the category name.
	4. Return true if the score is set successfully, false otherwise.
Reference: none
********************************************************************* */
bool Combinations::setScore(int category, int player_id){
    int score=0;
    int isValid = true;

    if (category >= 0 && category < 6) { // if between 0 to 5
		score = calculateUpperSectionScore(category + 1);
	}
	else if (category == 6) { // Three of a Kind
		if (hasThreeOfAKind()) {
			score = sumAllDice();
		}
        else
        {
			cout << "Three of a kind not available to score!" << endl;
        }
	}
	else if (category == 7) { // Four of a Kind
		if (hasFourOfAKind()) {
			score = sumAllDice();
		}
        else
        {
			cout << "Four of a kind not available to score!" << endl;
        }
	}
	else if (category == 8) { // Full House
		if (hasFullHouse()) {
			score = 25;
		}
        else
        {
			cout << "Full House not available to score!" << endl;
        }
	}
	else if (category == 9) { // Small Straight
		if (hasFourStraight()) {
			score = 30;
		}
        else
        {
			cout << "Four Straight not available to score!" << endl;
        }
	}
	else if (category == 10) { // Large Straight
		if (hasFiveStraight()) {
			score = 40;
		}
        else
        {
			cout << "Five Straight not available to score!" << endl;
        }
	}
	else if (category == 11) { // Yahtzee
		if (hasYahtzee()) {
			score = 50;
		}
        else
        {
			cout << "Yahtzee not available to score!" << endl;
        }
	}
	else {
		return false;
    }

    Round r;
    scoreCard[category].score = score;
	scoreCard[category].player_id = player_id;
	scoreCard[category].round_no = r.getRoundNo();
    cout << "\nScored : " << score << " points " << " at the category " << scoreCard[category].name;
    
    return true;
}

/* *********************************************************************
Function Name: hasScoreableCategory
Purpose: To check if there are any available combinations to score
Parameters:
    None
Return Value:
    - 'true' if there are available combinations to score, 'false' otherwise
Algorithm:
    1. Get the available combinations in a vecor.
    2. Check if any of the available combinations have not been scored.
    3. Return true if there are available combinations to score, false otherwise.
Reference: none
********************************************************************* */
bool Combinations::hasScoreableCategory() {

    vector <int> available = availableCombinations();
    // make sure none of them has been scored
    for (int i = 0; i < available.size(); i++) {
        if (scoreCard[available[i]].score == 0) {
            return true;
        }
    }
    return false;
}