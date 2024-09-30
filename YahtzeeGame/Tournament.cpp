#include "Tournament.h"


Tournament::Tournament() {
	humanRoll = 0;
	computerRoll = 0;

}

Tournament::~Tournament() {

}

void Tournament::startTournament() {

	Scorecard scorecard;
	//Round round(scorecard);
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
	// For the testing purpose, we will only have human play



	if (humanRoll > computerRoll)
	{
		round.playRoundP(1);
	}
	else
	{
		round.playRoundP(2);
	}

	do {
		// After the first round, find out the player with the lowest score and send it to the next round to start
		round.playRoundP(scorecard.playerWithLowestScore());
		//Round round2(scorecard, 2);
		//round2.playRound();
	} while (scorecard.isScorecardFull() == false);

	// The round will continue until both players have played

	// Displaying the final scorecard
	cout << endl;
	scorecard.displayScorecard();
	// Displaying the winner
	cout << "\n---------------------------" << endl;
	if (scorecard.getTotal(1) > scorecard.getTotal(2)) {
		cout << "You win!" << endl;
	}
	else if (scorecard.getTotal(1) < scorecard.getTotal(2)) {
		cout << "Computer wins!" << endl;
	}
	else {
		cout << "It's a tie!" << endl;
	}
	cout << "---------------------------" << endl;

}

void Tournament::endTournament() {

}