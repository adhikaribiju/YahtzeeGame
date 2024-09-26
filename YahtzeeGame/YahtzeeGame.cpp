
#include <iostream>
#include "stdafx.h"

#include "Tournament.h"


int main()
{

	Tournament game;

	cout << "Welcome to Yahtzee!" << endl;
	cout << endl;
	cout << "Please select one of the following" << endl;
	cout << "1. Start a new game" << endl;
	cout << "2. Load a saved game" << endl;
	cout << "3. Exit" << endl;
	cout << endl;

	int choice;
	cin >> choice;

	if (choice == 1) {
		cout << "Starting a new game..." << endl;
		game.startTournament();
	}
	else if (choice == 2) {
		cout << "Loading a saved game..." << endl;
	}
	else if (choice == 3) {
		cout << "Exiting..." << endl;
	}
	else {
		cout << "Invalid choice. Exiting..." << endl;
	} // will set the validation later on.




	return 0;
}
