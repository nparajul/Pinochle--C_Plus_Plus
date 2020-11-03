/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/



#include "pch.h"
#include <iostream>
#include "Game.h"

using namespace std;

/* *********************************************************************
Function Name: Game
Purpose: To construct a game object
Parameters:
Return Value: None
Algorithm: Initialize member variables
Assistance Received: None
********************************************************************* */
Game::Game() {

	this->isNewGame = true;
	this->gameRounds = 0;
	this->nextTurn = 0;
	players[0] = &user1;
	players[1] = &user2;

}

/* *********************************************************************
Function Name: ~Game
Purpose: To destruct a game object
Parameters:
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Game::~Game()
{

}

/* *********************************************************************
Function Name: beginGame
Purpose: To start a game
Parameters: None
Return Value: None
Local Variables:
Algorithm:
		Ask user if they'd like to start a new game or load a saved game, and call utility functions acordingly
Assistance Received: None
********************************************************************* */
void Game::beginGame() 
{
	cout << "--------------------Pinochle--------------------" << endl<<endl;

	string userInput;
	int inputInt;

	do {
		cout << "Please enter 1 to load a saved game or 2 to start a new game : ";
		cin >> userInput;


		try {
			inputInt = stoi(userInput);
		}
		catch (exception e)
		{
			cerr << "Invalid input" << endl;;
			inputInt = -1;
		}
	} while (inputInt != 1 && inputInt != 2);


	if (inputInt == 1)
	{
		loadSavedGame();
	}
	else
	{
		play();
	}

}

/* *********************************************************************
Function Name: play
Purpose: Main game loop
Parameters: None
Return Value: None
Local Variables:
	nextRoundInterestInt - int, value indicating if user wants to play a new round
	players - array of player pointer,  stores the addresses of the players in the game
	user1 - object of Human class, the human player of the game
	user2 - object of Computer class, the computer player of the game
Algorithm:
		1. Create human and computer objects and store their addresses in an array of pointer to a player.
		2. Facilitate coin toss to identifty the first player for the round
		3. Start a new round
		4. Print logistics after the end of the round.
		5. Contnue the process until user indicates to end.
		6. Identify game winner and print the output to the console.
Assistance Received: None
********************************************************************* */
void Game::play()
{

	int nextRoundInterestInt = 1;


	do
	{
		if (gameRounds == 0)
		{
			
			cout << "Let's do a coin toss!" << endl;
			this->nextTurn = coinToss();
			gameRounds++;
			
		}

		else if (isNewGame && gameRounds != 0 && (user1.getPlayerTotalScore() == user2.getPlayerTotalScore()))
		{
			cout << "Total Score is the same. Next Player will be determined by a coin toss." << endl;
			this->nextTurn = coinToss();

		}

		else if (isNewGame && gameRounds != 0 && (user1.getPlayerTotalScore() > user2.getPlayerTotalScore()))
		{
			cout << "Human Player has a higher total score and will play first for the next round." << endl;
			this->nextTurn = 0;

		}

		else if (isNewGame && gameRounds != 0 && (user1.getPlayerTotalScore() < user2.getPlayerTotalScore()))
		{
			cout << "Computer Player has a higher total score and will play first for the next round." << endl;
			this->nextTurn = 1;
		}
		
		
		cout << "----------------------------------------------------------" << endl;

		for (int i = 0; i < 2; i++)
		{
			players[i]->clearPilesandScores();
		}

		Round round(players, gameRounds, nextTurn);
		if (isNewGame == false)
		{
			round.loadRoundDetails(loadFileRoundDetails);
			isNewGame = true;
		}
		round.beginRound();

		user1.updatePlayerTotalScore(user1.getPlayerRoundScore());
		user2.updatePlayerTotalScore(user2.getPlayerRoundScore());

		cout << "-----------------------------End of Round " << gameRounds << "-----------------------------" << endl;
		
		

		cout << "Game Stats:" << endl;
		cout << "Human:" << endl;
		cout << "\tPrevious Round Score: " << user1.getPlayerRoundScore() << endl;
		cout << "\tTotal Score: " << user1.getPlayerTotalScore() << endl<<endl;
		cout << "Computer:" << endl;
		cout << "\tPrevious Round Score: " << user2.getPlayerRoundScore() << endl;
		cout << "\tTotal Score: " << user2.getPlayerTotalScore() << endl << endl;

		if (user1.getPlayerRoundScore() > user2.getPlayerRoundScore())
		{
			cout << "Round " << gameRounds << " winner: Human." << endl;
			
		}
		else if (user1.getPlayerRoundScore() < user2.getPlayerRoundScore())
		{
			cout << "Round " << gameRounds << " winner: Computer." << endl;

		}
		else
		{
			cout << "Round " << gameRounds << " was a tie." << endl;
		}

		
		
		string nextRoundInterest;
		do 
		{
			cout << "Would you like to play another round?[Input 1 for yes and 2 for no]" << endl;
			nextRoundInterest;
			cin >> nextRoundInterest;
			
			try
			{
				nextRoundInterestInt = stoi(nextRoundInterest);
			}
			catch (exception e)
			{
				cerr << "Invalid Input." << endl;
				nextRoundInterestInt = -1;
			}
		} while (nextRoundInterestInt != 1 && nextRoundInterestInt != 2);

		gameRounds++;

	} while (nextRoundInterestInt == 1);

	cout << "Game Winner : " ;

	if (user1.getPlayerTotalScore() > user2.getPlayerTotalScore())
	{
		cout << "Human" << endl<<endl;
	}
	else if (user1.getPlayerTotalScore() < user2.getPlayerTotalScore())
	{
		cout << "Computer" << endl<<endl;
	}
	else
	{
		cout << "Both users have the same points. The game ended as a tie" << endl;
	}
	cout << "Thank you for playing Pinochle." << endl;
		
}

/* *********************************************************************
Function Name: coinToss
Purpose: To do a coin toss
Parameters: None
Return Value: 
	index of the player who won the toss
Local Variables:
	tossResult - the result of the toss
Algorithm:
		1. Generate a random number between 1 and 2 and prompt user for their input.
		2. If user makes correct guess, return the index of the human player
		3. If not, return the index of computer player
Assistance Received: None
********************************************************************* */
int Game::coinToss()
{
	srand(time(NULL));
	int tossResult = (rand() % 2) + 1;
	string playerGuess;
	int guessVal;

	do 
	{
		cout << "Enter 1 for heads and 2 for Tails : ";
		cin >> playerGuess;
		try
		{
			guessVal = stoi(playerGuess);
		}
		catch (exception e)
		{
			cerr << "Invalid Input." << endl;
			guessVal = -1;
		}
	} while (guessVal != 1 && guessVal != 2);

	if(guessVal == tossResult)
	{
		cout << "Human Player has won the toss and will play first." << endl;
		return 0;
	}
	else
	{
		cout << "The computer has won the toss and will play first." << endl;
		return 1;
	}

}

/* *********************************************************************
Function Name: loadSavedGame
Purpose: To load a game from the saved file
Parameters: None
Return Value: None
Local Variables:
	fileName - string, name of the saved game file
	saveFile - object of ifstream to read from the saved file
Algorithm:
		1. Prompt user to enter the name of the saved file
		2. If the file exists, 
			3. Read from the file after performing reuired parsing
			3. Store the information read from the file in the loadFileRoundDetails vector
			4. Assign values to gameRounds and nextTurn member variables
			5. Play the game
		3. If not, display message to the output indicating so.
Assistance Received: None
********************************************************************* */
void Game::loadSavedGame()
{

	string fileName;
	int fileError=0;
	
	do
	{
		cout << "Please enter the name of the save file: ";
		cin >> fileName;
		fileName += ".txt";
		ifstream saveFile(fileName);

		if (!saveFile.is_open())
		{
			cerr << "Couldn't locate the file. Please enter a valid file." << endl;
			fileError = -1;
		}

		else
		{
			string line;
			getline(saveFile, line);
			this->gameRounds = stoi(getValueFromLoadLine(line));


			while (getline(saveFile, line))
			{
				if (!line.empty())
				{
					string next = getValueFromLoadLine(line);
					if (!(next.empty() && ( line == "Computer:" || line == "Human:")))
					{
						loadFileRoundDetails.push_back(removeLeadingSpaces(next));
					}
				}
			}

			if (loadFileRoundDetails[loadFileRoundDetails.size() - 1] == "Human")
			{
				this->nextTurn = 0;
			}
			else
			{
				this->nextTurn = 1;
			}

			loadFileRoundDetails.pop_back();
			this->isNewGame = false;
			play();

		}
	} while (fileError == -1);
	   	 
	

}

/* *********************************************************************
Function Name: getValueFromLoadLine
Purpose: To load stored value from each line
Parameters: 
	line - string, a single line text read from the saved file
Return Value: 
	the value stored in the line
Local Variables:
	pos, position of the ':' character in the line
Algorithm:
		1. Identify the position of ':' character in the line
		2. Return the rest of the string after the ':' character
Assistance Received: None
********************************************************************* */
string Game::getValueFromLoadLine(string line)
{
	auto pos = line.find(":");
	return line.substr(pos + 1);
}

/* *********************************************************************
Function Name: removeLeadingSpaces
Purpose: To remove leading spaces in a line
Parameters:
	line - string, a single line text read from the saved file
Return Value:
	the line after removing spaces
Local Variables:
	first - size_t, the first occurence position of space
Algorithm:
		1. Identify the position of space occurence
		2. Return the substring after the first occurence until the end
Assistance Received: None
********************************************************************* */
string Game::removeLeadingSpaces(string line)
{
	string removeVal = " \t";
	size_t first = line.find_first_not_of(removeVal);
	if (first == string::npos)
	{
		return "";
	}
	int last = line.size();
	int between = last - first + 1;
	return line.substr(first, between);
}