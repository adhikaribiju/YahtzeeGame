#include "Human.h"


Human::Human() {

	player_id = 1; // 1 for human, 2 for computer

	user_dice=""; // to store the user's input
	dice_to_reroll=0; //to store the user's dice that they wish to keep
	dice_num=0; // used for testing to specify the exact number in each dice
	category_choice=0;
	diceLocation = 0;
}

Human::~Human(){

}

void Human::playTurn() {
	cout << "\nYou are playing....." << endl;

	playRoll(); // Roll the 5 dice randomly
	displayDice(); // display the dice values

	Combinations board(dice); // retrive the combinations

	board.displayScorecard(); // display the available combinations
	board.displayAvailableCombinations(); // display the available combinations
	combinations = board.availableCombinations();
	keepDice.clear(); // clear the vector to store the dice that are kept
	player_choice = ' '; // to record the player's choice of dice roll

	while (num_rolls < max_rolls && player_choice != 'N') {
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


void Human::customFill() {
	// we are asking the user to fill in the dice array
	for (int i = 0; i < 5; i++) {
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
                for (int i = 0; i < num_of_dice; i++) {
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