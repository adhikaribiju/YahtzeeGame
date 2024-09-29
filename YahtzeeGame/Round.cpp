#include "Round.h"

//int Round::numOfRounds;

Round::Round() {

	this->player_id = 0;
	this->player_choice = ' ';

	// initializing the dice values to 0
	for (int i = 0; i < num_of_dice; i++) {
		dice.push_back(0);
	}

	//scorecard = sc;
	numOfRounds = 1;

}


//Round::Round(Scorecard sc, int player_id) {
//
//	sc.'displayScorecard'();
//	this->player_id = player_id;
//	this->player_choice = ' ';
//
//	// initializing the dice values to 0
//	for (int i = 0; i < num_of_dice; i++) {
//		dice.push_back(0);
//	}
//
//	scorecard = sc;
//	numOfRounds = 1;
//}


Round::~Round() {


}

void Round::playRound(int player_id) {

	cout << "Round " << numOfRounds << endl;

	// A roound constists of 2 turns
	playTurn(player_id); // play whoevers first turn it is

	if (player_id == 1)
	{
		playTurn(2); // play the other player's turn
	}
	else
	{
		playTurn(1);
	}

	numOfRounds++;

}

void Round::playTurn(int player_id) {
	// A turn consists of maximun of 3 rolls

	if (player_id == 1) cout << "\nHuman's turn" << endl;
	else cout << "\nComputer's turn" << endl;

	num_rolls = 1;
	int dice_to_keep, dice_num;
	string user_dice;
	vector<int> combinations;


	char player_choice = ' ';
	int category_choice = 0;

	int smth = 0; // test for git

	//scorecard.displayScorecard();

	playRoll();
	displayDice();
	Combinations aval_combinations(dice);

	aval_combinations.displayScorecard();
	aval_combinations.displayAvailableCombinations();

	while (num_rolls < max_rolls && player_choice != 'N') {
		cout << "Do you wish to roll again? (Y/N): ";
		cin >> player_choice;
		// Input validation
		while (player_choice != 'Y' && player_choice != 'N') {
			cout << "Invalid input. Please enter 'Y' or 'N': ";
			cin >> player_choice;
		}

		if (player_choice == 'Y') {

			do {
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
					else if (diceIndex(dice_to_keep) != -1)
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
				displayDice();
				aval_combinations.updateDice(dice);
				aval_combinations.displayAvailableCombinations();
			} while (dice_to_keep == -1);
			num_rolls++;
			player_choice = ' ';
		}
	} // end of while loopY


	combinations = aval_combinations.availableCombinations();
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
			if (aval_combinations.isCategoryFill(category_choice - 1))
			{
				cout << "Category already scored. Please choose another category." << endl;
			}
			else
			{
				// score the category
				//aval_combinations.setScore(category_choice - 1, dice, player_id);
				aval_combinations.setScore(category_choice - 1, player_id);
				hasScored = true;
			}

		} while (!hasScored);
	}
}


void Round::playRoundP(int player_id) {
	// A turn consists of maximun of 3 rolls

	Human human; //s create a human object
	Computer computer; // create a computer object


	cout << "\nRound " << numOfRounds << endl;



	if (player_id == 1) {
		human.playTurn();
		computer.playTurn();
	}
	else
	{
		computer.playTurn();
		human.playTurn();
	}
	numOfRounds++;
}

int Round::diceIndex(int dice_to_keep) {
	// find the index of the dice to keep
	for (int i = 0; i < num_of_dice; i++)
	{
		if (dice[i] == dice_to_keep)
		{
			return i;
		}
	}
	return -1;
}

void Round::playRoll() {
	// A roll consists of rolling 5 dice

	srand((unsigned)time(0));

	// genrate random number for five dice
	for (int i = 0; i < num_of_dice; i++) {
		dice[i] = ((rand() % 6) + 1);
	}

	cout << endl;
	// display the dice values

}

void Round::displayDice() {
	// display the dice values
	for (int i = 0; i < num_of_dice; i++)
	{
		cout << "Dice " << i + 1 << ": " << dice[i] << endl;
	}
	cout << endl;
}


