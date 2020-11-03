/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#include "pch.h"
#include "Computer.h"

/* *********************************************************************
Function Name: Computer
Purpose: To construct a computer object
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Computer::Computer()
{

}

/* *********************************************************************
Function Name: ~Computer
Purpose: To destruct a computer object
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Computer::~Computer()
{

}

/* *********************************************************************
Function Name: userTurn
Purpose: To provide menu options during the computer player's turn
Parameters:
	turnInfo - an object of the TurnInfo class which has all necessary information about the turn
Return Value: None
Local Variables: None
Algorithm: Taker user input and call utility functions accordingly
Assistance Received: None
********************************************************************* */
void Computer::userTurn(TurnInfo* turnInfo)
{
	this->trumpCard = turnInfo->getTrump();
	
	string userChoice;
	int choiceVal;

	do
	{
		cout << "Computer's Turn" << endl;
		cout << "Options:" << endl;
		cout << "\t1. Process computer's move" << endl;
		cout << "\t2. End the game" << endl;
		cout << "\t>";
		cin >> userChoice;
		try
		{
			choiceVal = stoi(userChoice);
		}
		catch (exception e)
		{
			cerr << "Invalid Input." << endl;
			choiceVal = -1;
		}

	} while (choiceVal < 1 || choiceVal > 2);

	switch (choiceVal)
	{
	case 1:
		makeMove(turnInfo);
		break;
	case 2:
		this->quitGame = true;
		break;
	default:
		cerr << "Invalid Input" << endl;
		exit(1);
	}

}

/* *********************************************************************
Function Name: makeMove
Purpose: To make a computer player's move
Parameters:
	turnInfo - an object of the TurnInfo class which has all necessary information about the turn
Return Value: None
Local Variables: None
Algorithm: 
	1. Identify if computer is a lead or a chase player.
	2. If lead player, call the bestLeadMove function. The function returns the best possible lead card.
	3. If chase player, call the bestChaseMove function. The function returns a map of cards that could win. Check if the computer can win the turn, and display recommendation accordingly.
	4. Display the reasoning for making the move on the console.
	5. Remove the played card from all necessary piles.
	6. Update computer's latestMove variable.
Assistance Received: None
********************************************************************* */
void Computer::makeMove(TurnInfo* turnInfo)
{
	int mostInexpensiveIndex = 0;
	
	if (turnInfo->getLeadPlayerIndex() == 0)
	{		
		bool isWinner = false;
		map<int, int> winningMap = bestChaseMove(turnInfo);
		if (winningMap.empty())
		{

			for (int i = 0; i < mPlayablePile.size(); i++)
			{
				if (mPlayablePile[i]->getSuit() == trumpCard->getSuit())
				{
					winningMap[i] = 100 + mPlayablePile[i]->convertFaceToPoints();
				}
				else
				{
					winningMap[i] = mPlayablePile[i]->convertFaceToPoints();
				}
			}
		}
		else
		{
			isWinner = true;
		}

		int CardPoints = INT_MAX;
		for (auto& t : winningMap)
		{
			if (t.second < CardPoints)
			{
				CardPoints = t.second;
				mostInexpensiveIndex = t.first;
			}
		}

		cout << endl << "The computer played ";
		mPlayablePile[mostInexpensiveIndex]->cardDescription();

		if (isWinner)
		{
			cout << " because it could win the turn.";
		}
		else
		{
			cout << " because it could not win the turn.";
		}
		cout << endl;


	}
	else
	{
		
		mostInexpensiveIndex = this->bestLeadMove(turnInfo);
		cout << endl << "The computer played ";
		mPlayablePile[mostInexpensiveIndex]->cardDescription();
		cout << " because it is the strongest card in hand after taking possible melds into account.";
		cout <<endl;

	}

	Card* playedCard = mPlayablePile[mostInexpensiveIndex];
	removePlayedCard(playedCard);
	this->latestMove = playedCard;

}

/* *********************************************************************
Function Name: declareMeld
Purpose: To declare computer's meld
Parameters:
Return Value: None
Local Variables:
	allValidMelds - map, a map containing all valid melds for the user's pile
Algorithm:
	1. Find all valid melds in computer's playable cards.
	2. If a meld is possible, 
		3. Display all possible meld with its name and cards to be used for it. 
		4. Declare the meld which yields most points and display the reasoning through console output.
		5. Update computer's meldMap, activeMeld, and setActiveMeldsNum value for all cards used in the meld.
	3. If a meld is not possible, display so to the console output.
Assistance Received: None
********************************************************************* */
void Computer::declareMeld()
{

	map<string, vector<vector<Card*>>> allValidMelds = totalPossibleMelds(mPlayablePile);

	int maxMeldPoints = 0;

	if (!allValidMelds.empty())
	{
		vector<Card*> meldCards;
		string meldType = "";
		for (auto& t : allValidMelds)
		{
			int meldPoints = getMeldPoints(t.first);

			if (meldPoints >= maxMeldPoints)
			{
				maxMeldPoints = meldPoints;
				meldType = t.first;
			}
			
		}

		meldCards = allValidMelds[meldType].front();
		for (int i = 0; i < meldCards.size(); i++)
		{
			this->updateMeldMap(meldCards[i], meldType);
		}
		this->activeMelds[meldType].push_back(meldCards);

		cout<<endl << "The computer declared a " << meldType << " meld and got "<<maxMeldPoints<<" points with the following cards: ";
		for (int i = 0; i < meldCards.size(); i++)
		{
			meldCards[i]->showCard();
			this->updateMeldMap(meldCards[i], meldType);
			meldCards[i]->setActiveMeldNums(1);
			mMeldPile.push_back(meldCards[i]);
			cout << " ";
		}
		cout << endl<<endl;

	}
	else
	{
		cout<<endl << "The computer does not have any valid melds to show for this turn. Moving on." << endl<<endl;
	}

	this->updatePlayerScore(maxMeldPoints);

}