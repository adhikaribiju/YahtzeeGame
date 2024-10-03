#include "Tournament.h"


Tournament::Tournament() {
	humanRoll = 0;
	computerRoll = 0;
}

Tournament::~Tournament() {

}

/* *********************************************************************
Function Name: startTournament
Purpose: To start the tournament
Parameters:
	None
Return Value:
	None
Algorithm:
	1. Roll the dice to determine who starts first
	2. Start the round with the winning player
	3. Continue the round until both players have played
	4. Display the winner of the tournament
Reference: None
********************************************************************* */
void Tournament::startTournament() {

	Scorecard scorecard;

	Round round;
	// Roll dice and determine who starts first - Human or Computer
	cout << "\nLet's roll the dice to see who gets the highest!\n" << endl;
	cout << "Press any key to roll the dice" << endl;
	cin.get();

	srand((unsigned)time(0));


	do {

		humanRoll = (rand() % 6) + 1;
		computerRoll = (rand() % 6) + 1;

		cout << "Human rolled: " << humanRoll << endl;
		cout << "Computer rolled: " << computerRoll << endl;

		if (humanRoll > computerRoll) {
			cout << "Congrats! You go first!" << endl;
		}
		else if (humanRoll < computerRoll) {
			cout << "Computer goes first!" << endl;
		}
		else {
			cout << "It's a tie! Let's roll again!" << endl;
			cout << "Press any key" << endl;
			cin.ignore();

		}
	} while (humanRoll == computerRoll);

	// After determining who starts first, the round will begin with that winning player

	if (humanRoll > computerRoll)
	{
		round.playRound(HUMAN);
	}
	else
	{
		round.playRound(COMPUTER);
	}

	do {
		// After the first round, find out the player with the lowest score and send it to the next round to start
		round.playRound(scorecard.playerWithLowestScore());
	} while (!scorecard.isScorecardFull());

	// The round will continue until both players have played // scorecard is full

	// Display the winner of the tournament
	cout << endl;
	scorecard.displayScorecard();
	displayWinner(scorecard.getTotal(1), scorecard.getTotal(2));

}

/* *********************************************************************
Function Name: loadTournament
Purpose: To load a tournament from a file
Parameters:
	None
Return Value:
	None
Algorithm:
	1. Ask the user for the file name
	2. Validate if the file exists
	3. Process the file
	4. Display the scorecard
	5. Start the round with the player with the lowest score
	6. Continue the round until both players have played
	7. Display the winner of the tournament
Reference: None
********************************************************************* */
void Tournament::loadTournament() {
	
	string fileName;

	cout << "Enter the file name: ";
	cin >> fileName;

	// Validate if the file exists
	if (!serialize.validateFile(fileName)) {
		cerr << "Error: File not found." << endl;
	}

	// Process the file 
	if (!serialize.readFile(fileName)) {
		cerr << "Error processing file." << endl;
	}
	else {
		// Display the scorecard
		serialize.displayLoadedScorecard();

		Scorecard scorecard;
		Round round;
		round.numOfRounds = serialize.getCurrentRound();

		cout << "\n\nHuman Score: " << scorecard.getTotal(HUMAN) << endl;
		cout << "Computer Score : " << scorecard.getTotal(COMPUTER) << endl;
		
	do {
		// After the first round, find out the player with the lowest score and send it to the next round to start
		round.resumeRound(scorecard.playerWithLowestScore());

	} while (!scorecard.isScorecardFull());

	// The round will continue until both players have played

	// Display the winner of the tournament
	cout << endl;
	scorecard.displayScorecard();
	displayWinner(scorecard.getTotal(1), scorecard.getTotal(2));

	}
}

/* *********************************************************************
Function Name: displayWinner
Purpose: To display the winner of the tournament
Parameters:
	player1, an integer
		the score of the human player
	player2, an integer
		the score of the computer player
Return Value:
	None
Algorithm:
	1. Display the final scorecard
	2. Display the winner
Reference: None
********************************************************************* */
void Tournament::displayWinner(int player1, int player2) {
	// Displaying the final scorecard
	cout << "\n\nYour Score: " << player1 << endl;
	cout << "Computer's Score: " << player2 << endl;
	
	// Displaying the winner
	cout << "\n---------------------------" << endl;
	if (player1 > player2) {
		cout << "You win!" << endl;
	}
	else if (player1 < player2) {
		cout << "Computer wins!" << endl;
	}
	else {
		cout << "It's a tie!" << endl;
	}
	cout << "---------------------------" << endl;
}