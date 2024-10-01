#pragma once
#include "stdafx.h"
#include "Scorecard.h"



class Combinations : public Scorecard {
public:
    // Constructor that accepts the dice vector
    Combinations(vector<int>& dice);
    Combinations();

    // Functions to check for various combinations
    bool hasThreeOfAKind();
    bool hasFourOfAKind();
    bool hasYahtzee();
    bool hasFullHouse();
    bool hasFourStraight();
    bool hasFiveStraight();

    // Functions to calculate scores
    int calculateUpperSectionScore(int number);
    int sumAllDice();

    // Function to determine and display available combinations
    void displayAvailableCombinations();

    //Function to record the available combinations in a vector 
    vector<int> availableCombinations();

    // Function to store the scores in the scorecard
    bool setScore(int category, int player_id);

    void updateDice(vector<int>& dice);

    void countDiceFace();


    bool hasScoreableCategory();

  // void setScore(int category, vector<int>& dice, int player_id);


private:
    vector<int> dice; // Stores the dice values
    vector<int> available_combinations;
    int counts[7];         // Frequency counts of dice values (indices 1-6)

    //int combination_count; // to count the available combinations



};