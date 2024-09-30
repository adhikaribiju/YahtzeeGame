#include "Serialization.h"

Serialization::Serialization()
{
    currentRound = 0;
}



Serialization::~Serialization()
{
}


bool Serialization::saveGame()
{
	// to save the game
    Round current_round;
	Scorecard current_scorecard;

    string fileName;

    // Ask the user for the file name
    cout << "Enter the name of the file to save the scorecard: ";
    cin >> fileName;

    // Open the file to write
    ofstream outFile(fileName);

    // Check if the file is opened successfully
    if (!outFile.is_open()) {
        cerr << "Error: Could not open the file for writing." << endl;
        return false;
    }

    // Write the current round number
    outFile << "Round: " << current_round.numOfRounds << endl;
    outFile << endl;  // Add an empty line
    outFile << "Scorecard:" << endl;

    // Write each score from the scoreCard
    for (int i = 0; i < 12; i++) {
        if (current_scorecard.scoreCard[i].score == 0) {
            // If the score is 0, write only 0
            outFile << "0" << endl;
        }
        else {
            // Otherwise, write the score, player, and round number
            string player = (current_scorecard.scoreCard[i].player_id == 1) ? "Human" : "Computer";
            outFile << current_scorecard.scoreCard[i].score << " " << player << " " << current_scorecard.scoreCard[i].round_no << endl;
        }
    }

    // Close the file
    outFile.close();
    cout << "Scorecard saved successfully to " << fileName << endl;
    return true;

}


void Serialization::loadGame()
{
	// to load the game
}


bool Serialization::validateFile(const string& fileName)
{
	ifstream file(fileName);
	return file.is_open();
}

bool Serialization::readFile(const string& fileName)
{
    
    ifstream file(fileName);
    string line;

    // Check the first line for round information
    getline(file, line);
    if (line.find("Round:") == string::npos) {
        cerr << "Error: Invalid format, missing round information." << endl;
        return false;
    }
    istringstream roundStream(line);
    string temp;
    roundStream >> temp >> currentRound;  // Extract the round number

    // Skip the next line "Scorecard:"
    getline(file, line);
    getline(file, line);
    if (line != "Scorecard:") {
        cerr << "Error: Expected 'Scorecard:' line." << endl;
        return false;
    }

	int i = 0; // index counter for scoreCard vector
    // Process score and player details
    while (getline(file, line)) {
        if (line.empty()) {
            continue;  // Skip empty lines
        }

        istringstream iss(line);
        int score, round_no;
        string player;

        // Try to extract the score first
        if (!(iss >> score)) {
            cerr << "Error: Invalid format in scorecard entry." << endl;
            return false;
        }

        // Skip lines where the score is zero (with no player or round_no)
        if (score == 0) {
            i++;
            continue;  // Do not process this line if score is 0
        }

        // Now check for player and round_no
        if (!(iss >> player >> round_no)) {
            cerr << "Error: Missing player or round_no for non-zero score." << endl;
            return false;
        }

        
        scorecard.scoreCard[i].score = score;
        scorecard.scoreCard[i].round_no = round_no;

        if (player.find("Human") != string::npos) {
            scorecard.scoreCard[i].player_id = 1;// Human
        }
        else if (player.find("Computer") != string::npos) {
            scorecard.scoreCard[i].player_id = 2;// Human
        }
        else {
            cerr << "Error: Invalid player information in scorecard." << endl;
            return false;
        }

        i++;
    }

    return true;

}


void Serialization::displayLoadedScorecard() {
	scorecard.displayScorecard();
}

int Serialization::getCurrentRound() {
	return currentRound;
}