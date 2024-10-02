#include "Human.h"


Human::Human() {

	player_id = 1; // 1 for human, 2 for computer

	user_dice=""; // to store the user's input
	dice_to_reroll=0; //to store the user's dice that they wish to keep
	dice_num=0; // used for testing to specify the exact number in each dice
	category_choice=0;
	diceLocation = 0;
    helpShown = false;
	keepFlag = false;
}

Human::~Human(){

}

/* *********************************************************************
Function Name: playTurn
Purpose: To play a turn for the human player
Parameters:
	None
Return Value: None
Algorithm:
	1. Roll the dice
	2. Display the dice values
	3. Display the available combinations
	4. Display the available categories
	5. Ask the user if they want to roll again
	6. If yes, ask the user to choose the dice to roll again
	7. If no, ask the user to choose a category to score
	8. Score the category if available
	9. End the turn
Reference: None
********************************************************************** */
void Human::playTurn() {
	cout << "\nYou are playing....." << endl;

	playRoll(); // Roll the 5 dice randomly
	displayDice(); // display the dice values

	Combinations board(dice); // retrive the combinations

	board.displayScorecard(); // display the available combinations
	board.displayAvailableCombinations(); // display the available combinations
	combinations = board.availableCombinations();
	viewHelp(dice); // Display help for the player
	keepDice.clear(); // clear the vector to store the dice that are kept
	player_choice = ' '; // to record the player's choice of dice roll

	while (num_rolls < MAX_ROLLS && player_choice != 'N') {
		cout << "\n\nDo you wish to roll again(Y/N):" << endl;
		cout << "Enter Y to roll again" << endl;
		cout << "Enter N to stand" << endl;
		cout << "Your choice(Y/N) : ";
		cin >> player_choice;
		// Input validation
		while (player_choice != 'Y' && player_choice != 'N') {
			cout << "Invalid input. Please enter 'Y' or 'N': ";
			cin >> player_choice;
		}
		if (player_choice == 'Y') {
			// user wants to re-roll the dice
			do{
					reRoll();
					displayDice();
					board.updateDice(dice);
					board.displayAvailableCombinations();
					combinations = board.availableCombinations();
                    viewHelp(dice);
			} while (dice_to_reroll == -1);

		num_rolls++;
		player_choice = ' ';
		}
	}
	
	// At this point dice roll has either been completed or the user has chosen not to roll again
	// Now the user has to choose a category to score IF AVAILABLE
	
    if (board.hasScoreableCategory()) {
        scoreCategory(board);
    }
    else
    {
		cout << "No category available to score. Next turn will be played by the other player." << endl;
    }
    
	cout << "\n\nYour Turn Ended!" << endl;
}

/* *********************************************************************
Function Name: customFill
Purpose: To fill the dice array with user input
Parameters:
	None
Return Value: None
Algorithm:
	1. Ask the user to enter the value for each dice
	2. Validate the input
	3. Fill the dice array with the user input
Reference: None
********************************************************************** */
void Human::customFill() {
	// we are asking the user to fill in the dice array
	for (int i = 0; i < DICE_COUNT; i++) {
		do {
			cout << "Enter the value for dice " << i + 1 << " : ";
			cin >> dice_num;
			if (dice_num < 1 && dice_num> 6)
			{
				cout << "Invalid entry! Enter values from 1-6 " << endl;
			}
			else
			{
				dice[i] = dice_num;
			}
		} while (dice_num < 1 && dice_num> 6);
	}
}

/* *********************************************************************
Function Name: scoreCategory
Purpose: To score a category for the human player
Parameters:
	board, an object of Combinations class - the scorecard
Return Value: None
Algorithm:
	1. Check if there is any category available to score
	2. If yes, ask the user to choose a category to score
	3. Score the category
Reference: None
********************************************************************** */
void Human::scoreCategory(Combinations board) {
	bool hasScored = false;
	if (!board.hasScoreableCategory())
	{
		cout << "No category available to score. Next turn will be played by the other player." << endl;
	}
	else
	{
		// check if the score is filled or not
		do {

			cout << "Enter the category number you wish to score: ";
			cin >> category_choice;

			// Input validation
			while ((category_choice < 1 || category_choice > 12)) {
				cout << "Invalid input. Please enter a number between 1 and 12: ";
				cin >> category_choice;
			}

			// check if the category is already scored
			if (board.isCategoryFill(category_choice - 1))
			{
				cout << "Category already scored. Please choose another category." << endl;
			}
			else
			{
				// score the category
				//aval_combinations.setScore(category_choice - 1, dice, player_id);
				
				board.setScore(category_choice - 1, player_id);
				//cout << "You have scored " << board.scoreCard[category_choice - 1].score << " points in the " << board.scoreCard[category_choice - 1].name << " category";
				hasScored = true;
			}

		} while (!hasScored);
	}
}

/* *********************************************************************
Function Name: reRoll
Purpose: To reroll the dice for the human player
Parameters:
	None
Return Value: None
Algorithm:
	1. Ask the user to choose the dice to reroll
	2. Validate the input
	3. Reroll the dice
Reference: None
********************************************************************** */
void Human::reRoll() {
    bool isValiddie = false;
    cout << "Enter the dice numbers you wish to roll again, separated by spaces." << endl;

    // Check if any dice have already been kept
    if (keepDice.empty()) {
        cout << "If you want to re-roll all dice, enter 0." << endl;
    }
    else {
        cout << "Note: These dice were kept previously: ";
        for (int i = 0; i < keepDice.size(); i++) {
            cout << dice[keepDice[i]] << " ";
        }
        cout << endl;
    }

    cout << "Your choice: ";
    cin.ignore();

    do {
        getline(cin, user_dice);
        istringstream iss(user_dice);
        vector<int> dices_toreroll;  // A vector to store valid dice numbers for rerolling
        isValiddie = false;  // Reset validation flag

        if (!user_dice.empty()) {
            while (iss >> dice_to_reroll) {
                // If dice_to_reroll == 0, try to reroll all dice, but only if keepDice is empty
                if (dice_to_reroll == 0 && keepDice.empty()) {
                    playRoll();  // Reroll all dice
                    keepDice.clear();  // Clear keepDice as all dice are rerolled
                    return;
                }
                else if (dice_to_reroll == 0 && !keepDice.empty()) {
                    // If there are kept dice, prevent rerolling all dice
                    cout << "You cannot reroll all dice because some dice have been kept." << endl;
                    cout << "Please choose specific dice to reroll." << endl;
                    isValiddie = false;
                    break;
                }
                else {
                    vector<int> indices = diceIndex(dice_to_reroll);  // Get dice indices for the number entered

                    if (!indices.empty()) {
                        // Process each index from diceIndex
                        for (int i = 0; i < indices.size(); i++) {
                            int dieIndex = indices[i];  // Current index of the dice

                            // Check if the dice at the current index has not been kept already
                            if (find(keepDice.begin(), keepDice.end(), dieIndex) == keepDice.end()) {
                                if (find(dices_toreroll.begin(), dices_toreroll.end(), dieIndex) == dices_toreroll.end()) {
                                    dices_toreroll.push_back(dieIndex);  // Add index to the list for reroll
                                    isValiddie = true;  // Set validation flag
                                    break;
                                }
                            }
                            else {
                                // If the dice was already kept
                                cout << "Dice " << dice_to_reroll << " is already kept and cannot be rerolled." << endl;
                            }
                        }
                    }
                    else {
                        // If dice_to_reroll does not correspond to any rolled dice
                        cout << "Invalid dice number: " << dice_to_reroll << ". Please enter valid dice numbers." << endl;
                        isValiddie = false;  // Reset validation flag for incorrect input
                    }
                }
            }

            if (isValiddie) {
                string choice;
                do {
                    // Asking user whether they want to manually input dice values or roll randomly
                    cout << "Do you wish to manually input the selected dice? (Y/N)" << endl;
                    getline(cin, choice);

                    if (choice == "Y" || choice == "y") {
                        // Let the user manually input the values for the dice they chose to reroll
                        for (int i = 0; i < dices_toreroll.size(); i++) {
                            int dieIndex = dices_toreroll[i];
                            do {
                                cout << "Enter the value for dice for  " << dice[dieIndex] << ": ";
                                cin >> dice[dieIndex];
                                if (dice[dieIndex] < 1 || dice[dieIndex] > 6) {
                                    cout << "Invalid entry! Enter values from 1-6." << endl;
                                }
                            } while (dice[dieIndex] < 1 || dice[dieIndex] > 6);  // Validate manual input
                        }
                        isValiddie = true;  // All dice manually input correctly
                    }
                    else if (choice == "N" || choice == "n") {
                        // Randomly reroll the dice that were chosen
                        cout << "Rolling the selected dice randomly..." << endl;
                        srand((unsigned)time(0));
                        for (int i = 0; i < dices_toreroll.size(); i++) {
                            int dieIndex = dices_toreroll[i];
                            dice[dieIndex] = ((rand() % 6) + 1);  // Random value between 1 and 6
                        }
                        isValiddie = true;  // Successfully rerolled
                    }
                    else {
                        cout << "Invalid entry! Enter Y or N." << endl;
                    }
                    cin.ignore();
                } while (choice != "N" && choice != "n" && choice != "Y" && choice != "y");

                // Now add only the unrolled dice (those not in dice_to_reroll) to keepDice
                for (int i = 0; i < DICE_COUNT; i++) {
                    // If the dice index is not in dice_to_reroll and not in keepDice already, add it to keepDice
                    if (find(dices_toreroll.begin(), dices_toreroll.end(), i) == dices_toreroll.end() &&
                        find(keepDice.begin(), keepDice.end(), i) == keepDice.end()) {
                        keepDice.push_back(i);
                    }
                }

            }
            else {
                cout << "Re-enter your choice: " << endl;
            }
        }
        else {
            cout << "No input detected. Please enter valid dice numbers." << endl;
        }
    } while (!isValiddie);  // Keep asking until valid dice numbers are entered
}


/* *********************************************************************
Function Name: findScorebyCategory
Purpose: To find the score for each category for the human player
Parameters:
	None
Return Value: None
Algorithm:
	1. Clear the availableScores vector
	2. Check if there are any available combinations
	3. Calculate the score for upper section category(1-6)
	4. Add the score to the availableScores vector
Reference: None
********************************************************************** */
void Human::findScorebyCategory() {

    availableScores.clear();
    if (help_board.availableCombinations().size() != 0) {

        for (int i = 1; i <= 6; i++)
        {
            int score = help_board.calculateUpperSectionScore(i);
            if (score != 0) availableScores.push_back({ i - 1, score });
        }

        int totalDice = help_board.sumAllDice();

        if (help_board.hasThreeOfAKind() && !help_board.isCategoryFill(6)) {
            availableScores.push_back({ 6, totalDice });
        }

        // Check for Four of a Kind
        if (help_board.hasFourOfAKind() && !help_board.isCategoryFill(7)) {
            availableScores.push_back({ 7, totalDice });
        }
        // Check for Full House
        if (help_board.hasFullHouse() && !help_board.isCategoryFill(8)) {
            availableScores.push_back({ 8, 25 });
        }

        // Check for Small Straight
        if (help_board.hasFourStraight() && !help_board.isCategoryFill(9)) {
            availableScores.push_back({ 9, 30 });
        }

        // Check for Large Straight
        if (help_board.hasFiveStraight() && !help_board.isCategoryFill(10)) {
            availableScores.push_back({ 10, 40 });
        }

        // Check for Yahtzee
        if (help_board.hasYahtzee() && !help_board.isCategoryFill(11)) {
            availableScores.push_back({ 11, 50 });
        }
    }
}

/* *********************************************************************
Function Name: viewHelp
Purpose: To provide help to the human player
Parameters:
	dice, a vector of integers - the dice values
Return Value: None
Algorithm:
	1. Ask the user if they want to use help
	2. If yes, find the score for each category
	3. If the highest score is >= 20, recommend the category with the highest score
	4. If the score is < 20, check if the lower section is available to score
		- If the lower section is filled, check if the upper section is available to score
			- If the upper section is available, check if there is any category available in dice
				- If yes, score the highest available
				- Otherwise, roll all dice
	5. Recommend the category with the highest score if score is greater than 10 and from upper section
	6. If the score is < 10, check if 3 or 4 of a kind is available
		- If yes, recommend scoring the 3/4 of a kind
		- Otherwise, check if 3 sequential numbers are available
			- If yes, check if five/four straight are available to score
				- If yes, keep the 3 sequential numbers and reroll the rest
			- If not, check for non-sequential numbers
	7. If no rolls left, score whatever is available
Reference: None
********************************************************************** */
void Human::viewHelp(vector<int>& dice) {
	int highestIndex = 0;
	int highestScore = 0;
	keepFlag = false;

	help_board.updateDice(dice);
    string choice;
    do {
        cout << "Do you want to use help? (Y/N): ";
        getline(cin, choice);

        if (choice == "Y" || choice == "y") {
            findScorebyCategory();
            //helpStrategy(dice);

            helpShown = false;

            //FIRST ROLL HERE

            keepDice.clear();

            if (keepFlag || !helpStrategy(dice)) {
                //score the max available if any
                 highestIndex = -1;
                 highestScore = -1;
                // Loop through the availableScores vector to find the category with the highest score
                for (int i = 0; i < availableScores.size(); i++) {
                    if (!help_board.isCategoryFill(availableScores[i].first)) {
                        if (availableScores[i].second > highestScore) {
                            highestScore = availableScores[i].second;
                            highestIndex = i;
                        }
                    }
                }


            }

            if (!helpShown) cout << "Try rolling all available dice since there are limited/no options at the moment." << endl;

        }
        else if (choice == "N" || choice == "n") {
            return;
        }
        else {
            // If the input is invalid, display error message
            cout << "Invalid entry! Please enter Y or N." << endl;
        }
    } while (choice != "Y" && choice != "y" && choice != "N" && choice != "n");


}


/* *********************************************************************
Function Name: helpStrategy
Purpose: To provide help in choosing the maximum score for the human player
Parameters:
	dice, a vector of integers - the dice values
Return Value: A boolean value
Algorithm:
	1. Check if there is any score >= 20
	2. If yes, recommend the category with the highest score
	3. If the score is < 20, check if the lower section is available to score
	- If the lower section is filled, check if the upper section is available to score
		- If the upper section is available, check if any category in dice right now
			- If yes, score the highest available
			- If not, roll all dice
		- If the score is >= 10, recommend the category with the highest score
	4. If the score is < 10, check if 3 or 4 of a kind is available
		- If yes, recommend scoring the 3/4 of a kind
		- If not, check if 3 sequential numbers are available
			- If yes, check if five/four straight are available to score
				- If yes, keep the 3 sequential numbers and reroll the rest
			- If not, check for non-sequential numbers
	- If no rolls left, score whatever is available
Reference: None
********************************************************************** */
bool Human::helpStrategy(vector<int>& dice) {
	helpShown = false;
	help_board.updateDice(dice);

	for (int i = static_cast<int>(availableScores.size()) - 1; i >= 0; i--) { // possible loss of data without that cast
		if (availableScores[i].second >= 20 && !help_board.isCategoryFill(availableScores[i].first)) {
			cout << "Category No. " << availableScores[i].first + 1 << " is recommended for scoring since it scores the highest." << endl;
			helpShown = true;
			return true; // category shown
		}
	}
	// If there is no score>=20
	if (!helpShown) {

		// Check if Lower Section is available to score
			// retrun false if lower section completely not filled

		if (lowerSectionFilled()) {

			// This means upper section is available to score
			// Do we have any category in dice right now?
			// If yes, score the highest available
			// If not, roll all dice
			if (!(availableScores.size() == 0))
			{
				displayHighestScore();
				return true; // category shown
			}
			else {
				cout << "Try rolling all the dice" << endl;
				helpShown = true;
					return true; // ALL DICE RE-ROLLED 
			}
		}
		else {
			// At this point, check if score availble is >=10
			// If Yes, Score it
			for (int i = static_cast<int>(availableScores.size()) - 1; i >= 0; i--) {
				if (availableScores[i].second >= 10 && !help_board.isCategoryFill(availableScores[i].first)) {
					cout << "Try scoring Category No: " << availableScores[i].first + 1 << " since it scores " << availableScores[i].second << endl;
					helpShown = true;
					return true; // category shown
				}
			}
			// If Not, check 3 or 4 of kind available
			if (!helpShown) {
				for (int i = static_cast<int>(availableScores.size()) - 1; i >= 0; i--) {
					// if 3/4 of a kind available, score it NO MATTER HOW SMALL THE SCORE
					if (availableScores[i].first + 1 == 7 || availableScores[i].first + 1 == 8) {
						cout << "You can try scoring " << "the 3/4 of a kind available since it scores " << availableScores[i].first << " points." << endl;
						helpShown = true;
						return true; // category shown
					}
				}
			}

			// From this point, we will try to keep certain dice faces and reroll the rest
			// Keep in mind that, you can only reroll the dice that hasn't be kept before
			// In the case, human chooses to reroll certain dice that were already kept, it will trigger roll conflict
			// Roll conflict will reroll all the other dices.

			// Check if dice has 3 sequential numbers
			// If yes, check if five/four straight are available to score
			//			If yes, keep the 3 sequential numbers and reroll the rest
			//			If no,	CHECK FOR Non-SEQUENTIAL NUMBERS

			if (!helpShown) {
				// Check for Non-SEQUENTIAL NUMBERS
				tryYahtzee();
				return false; // dice was kept or rerolled
			}

		}
	// No rolls left so score whatever available
		displayHighestScore();
		return true; // category shown
	}

	return false;
}


/* *********************************************************************
Function Name: lowerSectionFilled
Purpose: To check if the lower section is filled for the human player
Parameters:
	None
Return Value: 'true' if the lower section is filled, 'false' otherwise
Algorithm:
	1. Check if the lower section is filled
	2. If yes, return true
	3. If no, return false
Reference: None
********************************************************************** */
bool Human::lowerSectionFilled() {
	for (int i = 6; i < 12; i++)
	{
		if (help_board.scoreCard[i].player_id == 0) return false;
	}
	return true;
}

/* *********************************************************************
Function Name: displayHighestScore
Purpose: To display the highest score for the human player
Parameters:
	None
Return Value: None
Algorithm:
	1. Loop through the availableScores vector to find the category with the highest score
	2. If the category is not filled, display the category number
Reference: None
********************************************************************** */
void Human::displayHighestScore()
{
	for (int i = static_cast<int>(availableScores.size()) - 1; i >= 0; i--) {
		if (!help_board.isCategoryFill(availableScores[i].first)) {
			cout << "Category No. " << availableScores[i].first + 1 << " is recommended for scoring since it scores the highest." << endl;
			helpShown = true;
			return;
		}
	}
}

/* *********************************************************************
Function Name: isSequentialAvailable
Purpose: To check if a sequential is possible for the human player
Parameters:
	None
Return Value: 'true' if a sequential is possible, 'false' otherwise
Algorithm:
	1. Record the count of numbers on the dice
	2. Check for the specific consecutive sequences {1, 2, 3} or {2, 3, 4}
	3. If a sequence is found and the category is not filled, add dice involved in the sequence to keepDice
	4. Re-roll dice that are not part of the sequence
	5. Display the dice that can be rolled to obtain sequential numbers for 4 Straight or 5 Straight category
Reference: None
********************************************************************** */
bool Human::isSequentialAvailable()
{
	vector<int> count(7, 0);  // Initialize count vector with 7 elements, all set to 0
	vector<int> sequenceIndices; // To store indices of dice that match the sequence
	vector<int> dicelist; // to hold the dice that are not in sequential order
	int numOfOnes = 0;
	bool sequenceFound = false;
	bool diceRoll = false;
	int value = 0;

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

	if (sequenceFound && (!help_board.isCategoryFill(9) || !help_board.isCategoryFill(10))) {
		// Add dice involved in the sequence to keepDice
		for (int i = 0; i < dice.size(); ++i) {
			value = dice[i];
			if ((value == 1 || value == 2 || value == 3) ||  // For sequence {1, 2, 3}
				(value == 2 || value == 3 || value == 4)) {  // For sequence {2, 3, 4}
				// If the index is already in keepDice, set keepFlag to true
				if (find(keepDice.begin(), keepDice.end(), i) != keepDice.end()) {
					keepFlag = true;
				}
			}
		}

		if (!keepFlag) {
			// Re-roll dice that are not part of the sequence
			helpShown = true;
			for (int i = 0; i < dice.size(); ++i) {
				int value = dice[i];
				// Re-roll only dice that are not part of the sequence
				if ((value != 1 && value != 2 && value != 3) &&  // Not in {1, 2, 3}
					(value != 2 && value != 3 && value != 4)) {  // Not in {2, 3, 4}
					dicelist.push_back(value);
					diceRoll = true;
				}
			}
		}
		if (!dicelist.empty()) {
			cout << "You can try rolling: ";
				for (int i = 0; i < dicelist.size(); i++)
				{
					cout << dicelist[i] << " ";
				}
				helpShown = true;
				cout <<" to obtain sequential numbers for 4 Straight or 5 Straight category." << endl;
		}
		

		if (!diceRoll) {
			if (keepFlag) {
				cout << " all available dices. Some dice previously rolled are conflicting with the desired scores.";
				helpShown = true;
			}
		}
		cout << endl;
		return true;  // Sequence was found and dice were kept/rolled
	}

	return false;  // No valid sequence found

}

/* *********************************************************************
Function Name: tryYahtzee
Purpose: To see if Yahtzee is possible for the human player
Parameters:
	None
Return Value: None
Algorithm:
	1. Record the count of numbers on the dice
	2. Check if any dice number has count > 3 (three of a kind)
	3. If no three of a kind, check for two of a kind (count > 2)
	4. Choose the dice to roll based on the conditions
	5. Display the dice that can be rolled to obtain Yahtzee or Full House
Reference: None
********************************************************************** */
void Human::tryYahtzee() {
	bool threeOfAKind = false;
	bool twoOfAKind = false;
	int targetValueThreeOfAKind = -1;  // Target value for "three of a kind"
	int targetValueTwoOfAKind = -1;    // Target value for "two of a kind"
	int numOfones = 0;
	vector<int> count(7, 0);
	vector<int> dicelist; // to hold the dice that are not neither 2/3 of a kind 

	// Recording the count of numbers on the dice
	for (int die : dice) {
		if (die >= 1 && die <= 6) {
			count[die]++;
		}
	}

	// check if any dice number has count > 3 (three of a kind)
	for (int i = 1; i < count.size(); ++i) {
		if (count[i] >= 3) {
			threeOfAKind = true;
			targetValueThreeOfAKind = i;
		}
	}

	// if no three of a kind, check for two of a kind (count > 2)
	if (!threeOfAKind) {
		for (int i = 1; i < count.size(); ++i) {
			if (count[i] >= 2) {
				twoOfAKind = true;
				targetValueTwoOfAKind = i;
			}
		}
	}

	bool anyRolled = false;  // A flag to check if any dice is being rolled

	// choose the dice to roll based on the conditions
	for (int i = 0; i < dice.size(); ++i) {
		if (threeOfAKind) {
			// Roll all dice except those that have the value matching the three of a kind
			if (dice[i] != targetValueThreeOfAKind && (find(keepDice.begin(), keepDice.end(), i) == keepDice.end())) {
				dicelist.push_back(dice[i]);
				anyRolled = true;
			}
			else {
				// If the dice is already in keepDice, set keptError to true
				keepFlag = true;
			}
		}
		else if (twoOfAKind) {
			// Roll all dice except those that have the value matching the two of a kind
			if (dice[i] != targetValueTwoOfAKind && (find(keepDice.begin(), keepDice.end(), i) == keepDice.end())) {
				dicelist.push_back(dice[i]);
				anyRolled = true;
			}
			else {
				// If the dice is already in keepDice, set keptError to true
				keepFlag = true;
			}
		}
		else {
			// If no "three of a kind" or "two of a kind" found, roll all dice
			dicelist.push_back(dice[i]);
			anyRolled = true;
		}
	}

	if (dicelist.size() == DICE_COUNT) {
		cout << "You can try rolling all available dices. " << endl;
		helpShown = true;
	}
	else if (!dicelist.empty()) {
		cout << "You can try rolling: ";
			for (int i = 0; i < dicelist.size(); i++)
			{
				cout << dicelist[i] << " ";
			}
			helpShown = true;
			cout << " for Yahtzee or Full House." << endl;
	}

	cout << endl;
}