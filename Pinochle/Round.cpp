/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#include "pch.h"
#include"Round.h"
#include<fstream>


/* *********************************************************************
Function Name: Round
Purpose: To construct a round object
Parameters:
	players[], an array containg the adress of the player objects
	gameRounds, an unsigned int indicating the round number of the round being initialized
	nextTurn, an int value containing the index of the player making the next move
Return Value: None
Algorithm: Constructs a card object by initializing member variables.
Assistance Received: None
********************************************************************* */
Round::Round(Player* player[], unsigned int gameRounds,int nextTurn)
{
	this->players = player;
	this->mGameRounds = gameRounds;
	this->mRoundTurns = 0;
	this->leadPlayerIndex = nextTurn;
	this->chasePlayerIndex = (nextTurn + 1) % 2;
	this->isNewRound = true;

}

/* *********************************************************************
Function Name: ~Round
Purpose: To delete all card objects inside the different piles, and also delete the deck object initialized in the round
Parameters: None
Return Value: NA
Algorithm:	1. If the round is loaded from a saved game, then
				1. Delete all cards from user's and computer's capture pile
			2. Else, it's a round from a new game so all cards will be in tDeck. So instead of deleting each card here, call tDeck's destructor which will take care of it.
			3. Delete the tDeck object.
Assistance Received: None
********************************************************************* */
Round::~Round()
{
	
	if (tDeck->getDeck().size() != 48)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < players[i]->getCapturePile().size(); j++)
			{
				delete players[i]->getCapturePile()[j];
			}
		}
	}
	else
	{
		tDeck->~Deck();
	}

	delete tDeck;
}


/* *********************************************************************
Function Name: beginRound
Purpose: To start a new round
Parameters: None
Return Value: None
Local Variables:
		1. turnInfo, an object of the TurnInfo class containg all details that players need during a turn
Algorithm:
		1. If it is the first turn of the round,
			1. create a new deck
			2. deal 4 cards at a time to each player and repeat this 3 times.
			3. set the trump card
		2. Loop until the end of the round and on each loop, 
			1. Display game stats
			2. Allow players' to play a card
			3. Determine Turn winner based on the cards played and allow winner to declare a meld.
			4. Deal new cards to each player as per game's rule.
Assistance Received: None
********************************************************************* */
void Round::beginRound()
{
	if (isNewRound && mRoundTurns == 0)
	{
		tDeck = new Deck();
		tDeck->createNewDeck();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				dealCards(players[j], 4);
			}
		}
		mRoundTurns++;
		trumpCard = tDeck->drawCard();
		cout << endl;
	}
	
	while (mRoundTurns <25)
	{
		
		cout << "Round: " << mGameRounds << " Turn: " << mRoundTurns << endl;

		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				cout << "Human: " << endl;
			}
			else
			{
				cout << "Computer: " << endl;
			}
			players[i]->displayPlayerStats();
		}

		if (mRoundTurns <= 12)
		{
			cout << "Trump Card : ";
			trumpCard->showCard();
		}
		else
		{
			cout << "Trump Suit : ";
			cout<<trumpCard->getSuit();
		}
		cout << endl;
		cout << "Stock Pile : ";
		tDeck->displayStockPile();
		cout<<endl;

		

		string saveGameIntent;
		int saveGameIntentInt;

		do 
		{
			cout << "Would you like to save the game? [Please select 1 for yes and 2 for no]: ";
			cin >> saveGameIntent;

			try {
				saveGameIntentInt = stoi(saveGameIntent);
			}
			catch (exception e)
			{
				cerr << "Invalid Input." << endl;
				saveGameIntentInt = -1;
			}

		} while (saveGameIntentInt < 1 || saveGameIntentInt >2);

		if (saveGameIntentInt == 1)
		{
			saveGame();
			cout << "Thank you for playing." << endl;
			exit(1);
		}

		TurnInfo turnInfo(trumpCard, leadPlayerIndex);
		players[leadPlayerIndex]->userTurn(&turnInfo);
		cout << endl;

		if (players[leadPlayerIndex]->getQuitGame())
		{
			cout << "Thank you for playing." << endl;
			exit(1);
		}


		turnInfo.setLeadCard(players[leadPlayerIndex]->getLatestMove());
		players[chasePlayerIndex]->userTurn(&turnInfo);
		cout << endl;

		if (players[chasePlayerIndex]->getQuitGame())
		{
			cout << "Thank you for playing." << endl;
			exit(1);
		}

		leadPlayerIndex = determineTurnWinner(leadPlayerIndex,chasePlayerIndex);
		chasePlayerIndex = (leadPlayerIndex + 1) % 2;
			  
		cout << "Turn Winner : ";
		if (leadPlayerIndex == 0)
		{
			cout << "Human" << endl<<endl;
		}
		else
		{
			cout << "Computer" << endl;
		}
		

		players[leadPlayerIndex]->declareMeld();


		if (mRoundTurns < 12)
		{
			players[leadPlayerIndex]->dealSingleCard(tDeck->drawCard());
			players[chasePlayerIndex]->dealSingleCard(tDeck->drawCard());
		}
		if (mRoundTurns == 12)
		{
			cout << "Stock Pile is now empty." << endl;
			players[leadPlayerIndex]->dealSingleCard(tDeck->drawCard());
			players[chasePlayerIndex]->dealSingleCard(trumpCard);
		}

		mRoundTurns++;

	}
	
}

/* *********************************************************************
Function Name: dealCards
Purpose: To deal the next dealable card to a player
Parameters: 
		1. player, a pointer to the player who needs to be dealt a card
		2. cards, int value representing the number of cards to be dealt
Return Value: None
Local Variables: None
Algorithm: 
		1. Run a loop for cards time, and deal a new card from the deck to the player.
Assistance Received: None
********************************************************************* */
void Round::dealCards(Player* player, int cards)
{
	for (int i = 0; i < cards; i++)
	{
		player->dealSingleCard(tDeck->drawCard());
	}

}

/* *********************************************************************
Function Name: determineTurnWinner
Purpose: To determine the winner of a turn
Parameters:
		leadIndex, an int representing the index of the lead player
		chaseIndex, an int representing the index of the chase player
Return Value: 
		winnerindex, an int representing the index of the turn winner
Local Variables: 
		leadCard, card played by the lead player
		chaseCard, card played by the chase player
		leadCardValue, points that the lead card is worth
		chaseCardValue, points that the chase card is worth

Algorithm:
		1. Compare the cards played by the lead and chase players.
		2. Determine the index of the winner based on the rules of the game.
Assistance Received: None
********************************************************************* */
int Round::determineTurnWinner(int leadIndex, int chaseIndex)
{
	Card* leadCard = players[leadIndex]->getLatestMove();
	Card* chaseCard = players[chaseIndex]->getLatestMove();
	int leadCardValue = leadCard->convertFaceToPoints();
	int chaseCardValue = chaseCard->convertFaceToPoints();
	int winnerIndex;

	
	if (leadCard->getSuit() == chaseCard->getSuit())
	{
		if (leadCardValue >= chaseCardValue)
		{
			winnerIndex = leadIndex;
		}
		else
		{
			winnerIndex = chaseIndex;
		}

	}

	else 
	{
		if(chaseCard->getSuit() == trumpCard->getSuit())
		{ 
			winnerIndex = chaseIndex;
		}
		else
		{
			winnerIndex = leadIndex;
		}
	}
	
	players[winnerIndex]->addToCapturePile(leadCard);
	players[winnerIndex]->addToCapturePile(chaseCard);
	players[winnerIndex]->updatePlayerScore(leadCard->convertFaceToPoints());
	players[winnerIndex]->updatePlayerScore(chaseCard->convertFaceToPoints());

	return winnerIndex;
}

/* *********************************************************************
Function Name: saveGame
Purpose: To save a game to a config file
Parameters: None
Return Value: None
Local Variables:
		fileName - string, name of the save file
		saveFile - ofstream, output file stream object
		leadCardValue, points that the lead card is worth
		chaseCardValue, points that the chase card is worth

Algorithm:
		1. Get the name of the save file from the user
		2. Open the file, write all information that needs to be saved, and close the file.
Assistance Received: None
********************************************************************* */
void Round::saveGame()
{
	string fileName;
	cout << "Please enter the name of the file where you'd like to save the game: " ;
	cin >> fileName;
	fileName.append(".txt");
	ofstream saveFile;
	saveFile.open(fileName);
	saveFile << "Round: " << mGameRounds << "\n\n";
	saveFile << "Computer:\n";
	players[1]->savePlayersStats(saveFile);
	saveFile << "Human:\n";
	players[0]->savePlayersStats(saveFile);

	if (mRoundTurns > 12)
	{
		saveFile << "Trump Card: " << trumpCard->getSuit() << "\n";
	}
	else
	{
		saveFile << "Trump Card: " << trumpCard->getFace() << trumpCard->getSuit() << "\n";
	}
	saveFile << "Stock: ";
	for (int i = tDeck->firstCardPos() ; i < tDeck->getDeck().size(); i++)
	{
		saveFile << tDeck->getDeck()[i]->getFace() << tDeck->getDeck()[i]->getSuit();
		if (i + 1 != tDeck->getDeck().size())
		{
			saveFile << " ";
		}
	}
	saveFile << "\n\n";
	saveFile << "Next Player: ";
	if (leadPlayerIndex == 0)
	{
		saveFile << "Human";
	}
	else
	{
		saveFile << "Computer";
	}
	saveFile << "\n";	
	saveFile.close();

	cout << "Your Game has been saved" << endl;

}

/* *********************************************************************
Function Name: loadRoundDetails
Purpose: To load a round from a config file
Parameters: 
		savedRoundDetails - vector<string>, a vector containing the strings - retrieved from a config file - that represent the state of the game to be loaded
Return Value: None
Local Variables:
		trump - string, the string value of the trump card in the saved file
		Face - string, the face of the trump card
		Suit -string, the suit of the trump card
		totalCardsInCapture -int, total number of cards in each players' capture pile combined.
Algorithm: Get string values from the vector, 
				A. call corresponding load functions to restore the state, or
				B. Assign values to respective member variables.
Assistance Received: None
********************************************************************* */
void Round::loadRoundDetails(vector<string> savedRoundDetails)
{

	string trump = savedRoundDetails[8];

	if (trump.size() > 1)
	{
		string Face(1, trump[0]);
		string Suit(1, trump[1]);
		this->trumpCard = new Card(Face, Suit);
	}
	else
	{
		string Face(1, ' ');
		string Suit(1, trump[0]);
		this->trumpCard = new Card(Face, Suit);
	}

	
	char trumpSuit = trumpCard->getSuit()[0];

	tDeck = new Deck();
	tDeck->loadDeck(savedRoundDetails[9]);

	players[1]->loadScores(savedRoundDetails[0]);
	players[1]->loadHandPile(savedRoundDetails[1]);
	players[1]->loadCapturePile(savedRoundDetails[2]);
	players[1]->loadMeldPile(savedRoundDetails[3], trumpSuit);

	players[0]->loadScores(savedRoundDetails[4]);
	players[0]->loadHandPile(savedRoundDetails[5]);
	players[0]->loadCapturePile(savedRoundDetails[6]);
	players[0]->loadMeldPile(savedRoundDetails[7], trumpSuit);

	

	int totalCardsInCapture = (players[0]->getCapturePile().size()) + (players[1]->getCapturePile().size());
	mRoundTurns = (totalCardsInCapture / 2)+1;
	this->isNewRound = false;


}


