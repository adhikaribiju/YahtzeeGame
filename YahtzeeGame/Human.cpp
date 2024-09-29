#include "Human.h"


Human::Human() {

	player_id = 1; // 1 for human, 2 for computer

	user_dice=""; // to store the user's input
	dice_to_keep=0; //to store the user's dice that they wish to keep
	dice_num=0; // used for testing to specify the exact number in each dice
	category_choice=0;
}

Human::~Human(){

}

void Human::playTurn() {
	cout << "Human is playing....." << endl;

	playRoll(); // Roll the 5 dice randomly
	displayDice(); // display the dice values

	Combinations board(dice); // retrive the combinations

	board.displayScorecard(); // display the available combinations
	board.displayAvailableCombinations(); // display the available combinations
	combinations = board.availableCombinations();

	player_choice = ' '; // to record the player's choice of dice roll

	while (num_rolls < max_rolls && player_choice != 'N') {
		cout << "Do you wish to roll again? (Y/N): ";
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
			} while (dice_to_keep == -1);

		num_rolls++;
		player_choice = ' ';
		}
	}
	
	// At this point dice roll has either been completed or the user has chosen not to roll again
	// Now the user has to choose a category to score IF AVAILABLE
	scoreCategory(board);
}


void Human::reRoll() {
	cout << "Enter the dice numbers you wish to keep, seperated by spaces." << endl;
	cout << "If you want to re-roll all dice by entry, enter 0." << endl;
	cout << "Your choice: ";
	cin.ignore();


	getline(cin, user_dice);
	istringstream iss(user_dice);

	while (iss >> dice_to_keep)
	{
		if (dice_to_keep == 0)
		{
			customFill();
		}
		else if (diceIndex(dice_to_keep) != -1) // diceIndex validates the dice number
		{
			//roll the dice again
			srand((unsigned)time(0));
			dice[diceIndex(dice_to_keep)] = ((rand() % 6) + 1);
		}
		else
		{
			cout << "Invalid dice number : " << dice_to_keep << endl;
		}
	}
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
	if (combinations.size() == 0)
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
				hasScored = true;
			}

		} while (!hasScored);
	}
}