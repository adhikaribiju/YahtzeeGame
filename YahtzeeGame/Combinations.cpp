#include "Combinations.h"


Combinations::Combinations() {
	// Initialize counts to zero
	for (int i = 1; i <= 6; ++i) {
		counts[i] = 0;
	}
}
Combinations::Combinations(vector<int>& dice_values) {
    // Counting frequencies of each die face


    for (int i = 0; i < 5; i++) {
        dice.push_back(dice_values[i]);
    }

    // Initialize counts to zero
    for (int i = 1; i <= 6; ++i) {
        counts[i] = 0;
    }
}


bool Combinations::hasThreeOfAKind() {
    for (int i = 1; i <= 6; ++i) {
        if (counts[i] >= 3) {
            return true;
        }
    }
    return false;
}

bool Combinations::hasFourOfAKind() {
    for (int i = 1; i <= 6; ++i) {
        if (counts[i] >= 4) {
            return true;
        }
    }
    return false;
}

bool Combinations::hasYahtzee() {
    for (int i = 1; i <= 6; ++i) {
        if (counts[i] == 5) {
            return true;
        }
    }
    return false;
}

bool Combinations::hasFullHouse() {
    bool hasThree = false;
    bool hasTwo = false;
    for (int i = 1; i <= 6; ++i) {
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

bool Combinations::hasFourStraight() {
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

bool Combinations::hasFiveStraight() {
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

int Combinations::calculateUpperSectionScore(int number) {
    int sum = 0;
    for (int die : dice) {
        if (die == number) {
            sum += die;
        }
    }
    return sum;
}

int Combinations::sumAllDice() {
    int total = 0;
    for (int die : dice) {
        total += die;
    }
    return total;
}

vector<int> Combinations::availableCombinations() {
    available_combinations.clear();
    countDiceFace();
    // Upper Section (Aces to Sixes)
    for (int i = 1; i <= 6; ++i) {
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

void Combinations::displayAvailableCombinations() {
    countDiceFace();
    cout << "Dice: ";
    for (int die : dice) {
        cout << die << " ";
    }
    cout << "\n\n";

    // Upper Section (Aces to Sixes)
    for (int i = 1; i <= 6; ++i) {
        int score = calculateUpperSectionScore(i);
        if (score != 0) cout << "Score for " << i << "s: " << score << endl;
    }
    cout << endl;

    int totalDice = sumAllDice();

    // Check for Three of a Kind
    if (hasThreeOfAKind() && !isCategoryFill(6)) {
        cout << "Three of a Kind available! Score: " << totalDice << endl;
    }

    // Check for Four of a Kind
    if (hasFourOfAKind() && !isCategoryFill(7)) {
        cout << "Four of a Kind available! Score: " << totalDice << endl;
    }

    // Check for Full House
    if (hasFullHouse() && !isCategoryFill(8)) {
        cout << "Full House available! Score: 25" << endl;
    }

    // Check for Small Straight
    if (hasFourStraight() && !isCategoryFill(9)) {
        cout << "Four Straight available! Score: 30" << endl;
    }

    // Check for Large Straight
    if (hasFiveStraight() && !isCategoryFill(10)) {
        cout << "Five Straight available! Score: 40" << endl;
    }

    // Check for Yahtzee
    if (hasYahtzee()  && !isCategoryFill(11)) {
        cout << "Yahtzee! Score: 50" << endl;
    }
}



void Combinations::updateDice(vector<int>& dice_values) {
    dice.clear();
    for (int i = 0; i < 5; i++) {
        dice.push_back(dice_values[i]);
    }
}


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


bool Combinations::setScore(int category, int player_id)
{
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
	
    scoreCard[category].score = score;
	scoreCard[category].player_id = player_id;
    return true;
}