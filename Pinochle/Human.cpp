/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/


#include "pch.h"
#include "Human.h"


/* *********************************************************************
Function Name: Human
Purpose: To construct a human object
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Human::Human()
{

}

/* *********************************************************************
Function Name: ~Human
Purpose: To destruct a human object
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Human::~Human()
{

}

/* *********************************************************************
Function Name: userTurn
Purpose: To provide menu options during human player's turn
Parameters:
	turnInfo - an object of the TurnInfo class which has all necessary information about the turn
Return Value: None
Local Variables: None
Algorithm: Taker user input and call utility functions accordingly
Assistance Received: None
********************************************************************* */
void Human::userTurn(TurnInfo* turnInfo)
{
	this->trumpCard = turnInfo->getTrump();

	string userChoice;
	int choiceVal;
	int repeat = 0;

	do {
		cout << "Human's Turn" << endl;

		do
		{
			cout << "Options:" << endl;
			cout << "\t1. Make a move" << endl;
			cout << "\t2. I need help!" << endl;
			cout << "\t3. End the game" << endl;
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
		} while (choiceVal < 1 || choiceVal > 3);

		switch (choiceVal)
		{
		case 1:
			makeMove(turnInfo);
			repeat = 0;
			break;
		case 2:
			getHelp(turnInfo);
			repeat = 1;
			break;
		case 3:
			this->quitGame = true;
			repeat = 0;
			break;
		default:
			cerr << "Invalid Input" << endl;
			exit(1);
		}
	} while (repeat == 1);

}

/* *********************************************************************
Function Name: makeMove
Purpose: To facilitate a human player to make a move
Parameters:
	turnInfo - an object of the TurnInfo class which has all necessary information about the turn
Return Value: None
Local Variables: None
Algorithm: 
	1. Display cards from hand pile and meld pile to the user. 
	2. Take the user's input, remove the played card from all necesaary piles, and update the human's latest move variable.
Assistance Received: None
********************************************************************* */
void Human::makeMove(TurnInfo* turnInfo)
{

	string cardChoice;
	int cardChoiceVal;
	int totalSize = mHandPile.size() + mMeldPile.size();
	do {
		cout << "Please choose a card that you'd like to play." << endl;
		int i;
		cout << "Hand Pile: ";
		for (i = 0; i < mHandPile.size(); i++)
		{
			mHandPile[i]->showCard();
			cout << "(" << i + 1 << ") ";
		}

		cout << "Meld Pile: ";
		for (int j = 0; j < mMeldPile.size(); j++)
		{
			mMeldPile[j]->showCard();
			cout << "(" << i + 1 << ") ";
			i++;
		}
		cout << endl;

		cout << ">";
		cin >> cardChoice;
		try
		{
			cardChoiceVal = stoi(cardChoice);
		}
		catch (exception e)
		{
			cerr << "Invalid Input." << endl;
			cardChoiceVal = -1;
		}

		if (cardChoiceVal < 1 || cardChoiceVal > totalSize)
		{
			cout << "Invalid Input. Please select an index from 1 to " << totalSize << endl;
			
		}

	} while (cardChoiceVal < 1 || cardChoiceVal > totalSize);

	Card* playedCard;
	if (cardChoiceVal <= mHandPile.size())
	{
		playedCard = mHandPile[cardChoiceVal - 1];
	}
	else
	{
		int meldPileIndex = cardChoiceVal - mHandPile.size();
		playedCard = mMeldPile[meldPileIndex - 1];

		
	}
	cout << endl << "Played: ";
	playedCard->cardDescription();
	cout << endl ;


	removePlayedCard(playedCard);
	this->latestMove = playedCard;
}

/* *********************************************************************
Function Name: declareMeld
Purpose: To provide meld declaration options to the human player
Parameters:
	turnInfo - an object of the TurnInfo class which has all necessary information about the turn
Return Value: None
Local Variables: 
	noMeld - bool, a flag indicating whether a usr wants to declare a meld or not
	meldCards - vector, a list of cards supplied by the user for the meld
Algorithm:
	1. Display meld declaration options.
	2. If user wants to declare a meld - Take the user's input and validate the meld. 
		3. For a valid meld - Update meldMap, activemelds, and activeMeldsUsedFor values for the cards. Display the meld earned for that input.
	4. Else if user wants needs help, call the meldHelp utility function.
	5. Else, acknowledge the fact that user doesn't want to declare a meld and continue the meld.
Assistance Received: None
********************************************************************* */
void Human::declareMeld()
{
	bool noMeld = false;
	do 
	{
		string meldDeclarationOption;
		int meldDeclarationOptionInt;
		vector<Card*> meldCards;

		do
		{
			
			cout << "Meld Declaration Options:" << endl;
			cout << "\t1. Declare a Meld. " << endl;
			cout << "\t2. I need help." << endl;
			cout << "\t3. I do not want to declare a meld." << endl;
			cout << "\t>";

			cin >> meldDeclarationOption;
			try
			{
				meldDeclarationOptionInt = stoi(meldDeclarationOption);
			}
			catch (exception e)
			{
				cout << "Invalid Input." << endl;
				meldDeclarationOptionInt = -1;
			}
		} while (meldDeclarationOptionInt < 1 || meldDeclarationOptionInt > 3);

		if (meldDeclarationOptionInt == 2)
		{
			meldHelp();
		}

		else if (meldDeclarationOptionInt == 1)
		{
			cout << endl;

			int i;
			cout << "Hand Pile: ";
			for (i = 0; i < mHandPile.size(); i++)
			{
				mHandPile[i]->showCard();
				cout << "(" << i + 1 << ") ";
			}


			cout << "Meld Pile: ";
			for (int j = 0; j < mMeldPile.size(); j++)
			{
				mMeldPile[j]->showCard();
				cout << "(" << i + 1 << ") ";
				i++;
			}

			cout << endl<<endl;

			cout << "Please select the index/indices of card/s for the meld (Press -1 when you're done.): " << endl;

			string cardChoice;
			int cardChoiceVal;
			do {
				int totalSize = mHandPile.size() + mMeldPile.size();
				
				do {
					cin >> cardChoice;
					try
					{
						cardChoiceVal = stoi(cardChoice);
					}
					catch (exception e)
					{
						cerr << "Invalid Input."<< endl;
						cardChoiceVal = -2;
					}

					if ((cardChoiceVal < 1 && cardChoiceVal != -1) || cardChoiceVal > totalSize)
					{
						cerr << "Invalid Input. Please select an option between 1 and " << totalSize << endl;
					}
				} while ((cardChoiceVal < 1 && cardChoiceVal!=-1) || cardChoiceVal > totalSize);

				
				if (cardChoiceVal != -1)
				{
					Card* chosenCard;
					if (cardChoiceVal <= mHandPile.size())
					{
						chosenCard = mHandPile[cardChoiceVal - 1];
					}
					else
					{
						int meldPileIndex = cardChoiceVal - mHandPile.size();
						chosenCard = mMeldPile[meldPileIndex - 1];
					}

					meldCards.push_back(chosenCard);
				}
			} while (cardChoiceVal != -1);
			

			int meldPoints = validateMeldCards(meldCards);
			if (meldPoints > 0)
			{
				vector<string> cardValues;
				for (int i = 0; i < meldCards.size(); i++)
				{
					cardValues.push_back(meldCards[i]->getFace() + meldCards[i]->getSuit());
				}
				char trumpSuit = trumpCard->getSuit()[0];
				string meldType = getMeldType(cardValues,trumpSuit);
				for (int i = 0; i < meldCards.size(); i++)
				{
					this->updateMeldMap(meldCards[i], meldType);
					meldCards[i]->setActiveMeldNums(1);
					mMeldPile.push_back(meldCards[i]);
				}
				this->activeMelds[meldType].push_back(meldCards);
				this->updatePlayerScore(meldPoints);
				cout << "You've earned " << meldPoints << " points for that " << meldType << " meld." << endl<<endl;
				noMeld = true;
			}
			else
			{
				cout << "That's not a valid meld!" << endl;
				meldCards.clear();
			}
		}
		else
		{
			cout << "Player didn't want to declare a meld. Moving on." << endl<<endl;
			noMeld = true;
		}

	} while (noMeld == false);

}

/* *********************************************************************
Function Name: getHelp
Purpose: To recommend a move to the human player 
Parameters:
Return Value: None
Local Variables:
	mostInexpensiveIndex - int, the index of the card that is recommended to the human player
Algorithm:
	1. Identify if the human is a lead player or a chase player.
	2. If lead player, call the bestLeadMove function used by the computer to make its move. The function returns the best possible lead card.
	3. If chase player, call the bestChaseMove function used by the computer to make its move. The function returns a map of cards that could win. Check if the user can win the turn, and display recommendation accordingly.
	4. Display the recommendation to the human player on the console.
Assistance Received: None
********************************************************************* */
void Human::getHelp(TurnInfo* turnInfo)
{
	int mostInexpensiveIndex = 0;
	if (turnInfo->getLeadPlayerIndex() == 0)
	{
		mostInexpensiveIndex = this->bestLeadMove(turnInfo);
		cout << endl;
		cout<< "I recommend you play ";
		mPlayablePile[mostInexpensiveIndex]->cardDescription();
		cout << " because it is the strongest card in hand after taking possible melds into account.";
		cout << endl << endl;
	}
	else
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

		cout << endl;
		cout<< "I recommend you play ";
		mPlayablePile[mostInexpensiveIndex]->cardDescription();

		if (isWinner)
		{
			cout << " because it could win the turn.";
		}
		else
		{
			cout << " because you could not win the turn.";
		}
		cout << endl << endl;
	}

}

/* *********************************************************************
Function Name: meldHelp
Purpose: To recommend a meld to the human player
Parameters:
Return Value: None
Local Variables:
	allValidMelds - map, a map containing all valid melds for the user's pile
Algorithm:
	1. Use computer's strategy to find all possible melds for the user. 
	2. If a meld is possible, Display all possible meld with its name and cards to be used for it. Find the meld which yields most points and recommend it to the user through console output.
	3. If a meld is not possible, display so to the console output.
Assistance Received: None
********************************************************************* */
void Human::meldHelp()
{
	map<string, vector<vector<Card*>>> allValidMelds = totalPossibleMelds(mPlayablePile);
	int maxMeldPoints = 0;
	
	if (!allValidMelds.empty())
	{

		cout << "The available valid melds for this turn are as follows:" << endl;

		for (auto& t : allValidMelds)
		{
			
			cout << t.first << " : " << endl;
			for (int i = 0; i < t.second.size(); i++)
			{
				for (int j = 0; j < t.second[i].size(); j++)
				{
					if (j == 0)
					{
						cout << "> ";
					}
					(t.second[i])[j]->showCard();
					cout << " ";
				}
				cout << endl;
				
			}


		}
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
		
		cout << "I recommend you declare a " << meldType << " meld with the following cards because it yields "<<maxMeldPoints<<" points : ";
		for (int i = 0; i < meldCards.size(); i++)
		{
			meldCards[i]->showCard();
			cout << " ";
		}
		cout << endl << endl;

	}
	else
	{
		cout << "You do not have any valid melds to show for this turn." << endl;
	}
}
