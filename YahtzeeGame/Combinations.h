#pragma once
#include "stdafx.h"
#include "Scorecard.h"



class Combinations : public Scorecard {
public:

    Combinations();
    // Constructor that accepts the dice vector
    Combinations(vector<int>& dice);
  

    // to store the scores in the scorecard
    bool setScore(int category, int player_id);

    // Functions to calculate scores
    int calculateUpperSectionScore(int number);
    int sumAllDice();

	// update the dice values
    void updateDice(vector<int>& dice);

    //to return available combinations in a vector 
    vector<int> availableCombinations();

    // Functions to check for various combinations
    bool hasThreeOfAKind() const;
    bool hasFourOfAKind() const;
    bool hasYahtzee() const;
    bool hasFullHouse() const;
    bool hasFourStraight() const;
    bool hasFiveStraight() const;


    // Functions to determine and display available combinations
    bool hasScoreableCategory();
    void displayAvailableCombinations();
    void countDiceFace();




private:

    const int DICE_COUNT = 5;
    const int MAX_DICE_VALUE = 6;

    vector<int> dice; // Stores the dice values
    vector<int> available_combinations; // stores the category numbers of the combinations available given dice combinations
    int counts[7];  // Frequency counts of dice values (indices 1-6)
};