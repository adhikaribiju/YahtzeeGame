#pragma once
#include "stdafx.h"
#include "Scorecard.h"



class Combinations : public Scorecard {
public:

    Combinations();
    // Constructor that accepts the dice vector
    Combinations(vector<int> dice);
  

    // to store the scores in the scorecard
    bool setScore(int category, int player_id);

    // update the dice values
    void updateDice(vector<int> dice);

    //to return available combinations in a vector 
    vector<int> availableCombinations();

    // Functions to calculate scores
    int calculateUpperSectionScore(int number);
    int sumAllDice();

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

    // to store the number of dice in the game
    const int DICE_COUNT = 5;
    // to store the maximum value of the dice
    const int MAX_DICE_VALUE = 6;

    // Stores the dice values
    vector<int> dice; 
    // stores the category numbers of the combinations available on dice values
    vector<int> available_combinations; 
    // Frequency counts of dice values (indices 1-6)
    int counts[7]; 
};