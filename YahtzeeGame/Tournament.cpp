#include "Tournament.h"


Tournament::Tournament() {
	humanRoll = 0;
	computerRoll = 0;
}

Tournament::~Tournament() {

}

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
		
	do {
		// After the first round, find out the player with the lowest score and send it to the next round to start
		round.playRound(scorecard.playerWithLowestScore());

	} while (scorecard.isScorecardFull() == false);

	// The round will continue until both players have played

	// Display the winner of the tournament
	cout << endl;
	scorecard.displayScorecard();
	displayWinner(scorecard.getTotal(1), scorecard.getTotal(2));

	}
}

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