#include "Serialization.h"

Serialization::Serialization()
{
    currentRound = 0;
}



Serialization::~Serialization()
{
}

/* *********************************************************************
Function Name: saveGame
Purpose: To save the game
Parameters:
    None
Return Value:
    'true' if the game is saved successfully, 'false' otherwise
Algorithm:
    1. Ask the user for the file name
    2. Open the file to write
    3. Write the current round number
    4. Write each score from the scoreCard, 0 in the line if the score is 0
    5. Return true if the game successfully written to the file
    6. Otherwise, return false
Reference: None
********************************************************************* */
bool Serialization::saveGame()
{
	// to save the game
    Round current_round;
	Scorecard current_scorecard;

    string fileName;

    // Ask the user for the file name
    cout << "Enter the name of the file to save the scorecard: ";
    cin >> fileName;

	fileName = fileName + ".txt";

    // Open the file to write
    ofstream outFile(fileName);

    // Check if the file is opened successfully
    if (!outFile.is_open()) {
        cerr << "Error: Could not open the file for writing." << endl;
        return false;
    }

    // Write the current round number
    outFile << "Round: " << current_round.numOfRounds-1 << endl;
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



/* *********************************************************************
Function Name: validateFile
Purpose: To check if the file exists
Parameters:
    fileName, a string
        the name of the file
Return Value:
    'true' if the file exists, 'false' otherwise
Algorithm:
    1. Open the file
    2. Check if the file is opened successfully
	3. Return true if the file is opened successfully, otherwise return false
Reference: None
********************************************************************* */
bool Serialization::validateFile(const string& fileName)
{
	ifstream file(fileName);
	return file.is_open();
}

/* *********************************************************************
Function Name: readFile
Purpose: To process the file
Parameters:
    fileName, a string
        the name of the file
Return Value:
    'true' if the file is processed successfully, 'false' otherwise
Algorithm:
    1. Open the file
    2. Read the round information
    3. If 0 or blank, skip the line
    4. Extract the score, player, and round_no
    5. Check for player and round_no
    6. If the player is Human, set the player_id to 1
    7. If the player is Computer, set the player_id to 2
    8. Continue processing the file
    9. store the result in scorecard object
    10. If error, return false
    4. Otherwise, return true
Reference: None
********************************************************************* */
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

/* *********************************************************************
Function Name: displayLoadedScorecard
Purpose: To display the loaded scorecard
Parameters:
    None
Return Value:
    None
Algorithm:
	1. Call the displayScorecard function from the scorecard object
Reference: None
********************************************************************* */
void Serialization::displayLoadedScorecard() {
	scorecard.displayScorecard();
}

/* *********************************************************************
Function Name: getCurrentRound
Purpose: getter function to return the current round
Parameters:
    None
Return Value:
    the current round
Reference: None
********************************************************************* */
int Serialization::getCurrentRound() {
	return currentRound;
}